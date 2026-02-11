ene_sd_init(struct us_data *us)
{
	int result;
	struct bulk_cb_wrap *bcb = (struct bulk_cb_wrap *) us->iobuf;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;
	u8 *bbuf = info->bbuf;

	usb_stor_dbg(us, "transport --- ENE_SDInit\n");

	result = ene_load_bincode(us, SD_INIT1_PATTERN);
	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Load SD Init Code Part-1 Fail !!\n");
		return USB_STOR_TRANSPORT_ERROR;
	}

	memset(bcb, 0, sizeof(struct bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->Flags = US_BULK_FLAG_IN;
	bcb->CDB[0] = 0xF2;

	result = ene_send_scsi_cmd(us, FDIR_READ, NULL, 0);
	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Execution SD Init Code Fail !!\n");
		return USB_STOR_TRANSPORT_ERROR;
	}


	result = ene_load_bincode(us, SD_INIT2_PATTERN);
	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Load SD Init Code Part-2 Fail !!\n");
		return USB_STOR_TRANSPORT_ERROR;
	}

	memset(bcb, 0, sizeof(struct bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x200;
	bcb->Flags              = US_BULK_FLAG_IN;
	bcb->CDB[0]             = 0xF1;

	result = ene_send_scsi_cmd(us, FDIR_READ, bbuf, 0);
	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Execution SD Init Code Fail !!\n");
		return USB_STOR_TRANSPORT_ERROR;
	}

	info->SD_Status =  *(struct SD_STATUS *) bbuf;
	if (info->SD_Status.Insert && info->SD_Status.Ready) {
		struct SD_STATUS *s = &info->SD_Status;

		ene_get_card_status(us, bbuf);
		usb_stor_dbg(us, "Insert     = %x\n", s->Insert);
		usb_stor_dbg(us, "Ready      = %x\n", s->Ready);
		usb_stor_dbg(us, "IsMMC      = %x\n", s->IsMMC);
		usb_stor_dbg(us, "HiCapacity = %x\n", s->HiCapacity);
		usb_stor_dbg(us, "HiSpeed    = %x\n", s->HiSpeed);
		usb_stor_dbg(us, "WtP        = %x\n", s->WtP);
	} else {
		usb_stor_dbg(us, "SD Card Not Ready --- %x\n", bbuf[0]);
		return USB_STOR_TRANSPORT_ERROR;
	}
	return USB_STOR_TRANSPORT_GOOD;
}
