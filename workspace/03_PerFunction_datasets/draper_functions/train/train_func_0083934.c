SCSI_Write10 (uint8_t lun , uint8_t *params) {
	if (MSC_BOT_State == BOT_IDLE) {


		if ((MSC_BOT_cbw.bmFlags & 0x80) == 0x80) {
			SCSI_SenseCode(MSC_BOT_cbw.bLUN,
						   ILLEGAL_REQUEST,
						   INVALID_CDB);
			return -1;
		}


		if(USBD_STORAGE_fops->IsReady(lun) !=0 ) {
			SCSI_SenseCode(lun,
						   NOT_READY,
						   MEDIUM_NOT_PRESENT);
			return -1;
		}


		if(USBD_STORAGE_fops->IsWriteProtected(lun) !=0 ) {
			SCSI_SenseCode(lun,
						   NOT_READY,
						   WRITE_PROTECTED);
			return -1;
		}


		SCSI_blk_addr = (params[2] << 24) | \
						(params[3] << 16) | \
						(params[4] <<  8) | \
						params[5];
		SCSI_blk_len = (params[7] <<  8) | \
					   params[8];


		if(SCSI_CheckAddressRange(lun, SCSI_blk_addr, SCSI_blk_len) < 0) {
			return -1;
		}

		SCSI_blk_addr *= SCSI_blk_size;
		SCSI_blk_len  *= SCSI_blk_size;


		if (MSC_BOT_cbw.dDataLength != SCSI_blk_len) {
			SCSI_SenseCode(MSC_BOT_cbw.bLUN,
						   ILLEGAL_REQUEST,
						   INVALID_CDB);
			return -1;
		}


		MSC_BOT_State = BOT_DATA_OUT;
		DCD_EP_PrepareRx (cdev,
						  MSC_OUT_EP,
						  MSC_BOT_Data,
						  MIN (SCSI_blk_len, MSC_MEDIA_PACKET));
	} else {
		return SCSI_ProcessWrite(lun);
	}
	return 0;
}
