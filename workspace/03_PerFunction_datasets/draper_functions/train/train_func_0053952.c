ips_flash_copperhead(ips_ha_t * ha, ips_passthru_t * pt, ips_scb_t * scb)
{
	int datasize;


	if (IPS_IS_TROMBONE(ha) && pt->CoppCP.cmd.flashfw.type == IPS_FW_IMAGE) {
		if (ips_usrcmd(ha, pt, scb))
			return IPS_SUCCESS;
		else
			return IPS_FAILURE;
	}
	pt->BasicStatus = 0x0B;
	pt->ExtendedStatus = 0;
	scb->scsi_cmd->result = DID_OK << 16;


	if (pt->CoppCP.cmd.flashfw.type == IPS_BIOS_IMAGE &&
	    pt->CoppCP.cmd.flashfw.direction == IPS_ERASE_BIOS) {
		pt->BasicStatus = 0;
		return ips_flash_bios(ha, pt, scb);
	} else if (pt->CoppCP.cmd.flashfw.packet_num == 0) {
		if (ips_FlashData && !test_and_set_bit(0, &ips_FlashDataInUse)){
			ha->flash_data = ips_FlashData;
			ha->flash_busaddr = ips_flashbusaddr;
			ha->flash_len = PAGE_SIZE << 7;
			ha->flash_datasize = 0;
		} else if (!ha->flash_data) {
			datasize = pt->CoppCP.cmd.flashfw.total_packets *
			    pt->CoppCP.cmd.flashfw.count;
			ha->flash_data = pci_alloc_consistent(ha->pcidev,
					                      datasize,
							      &ha->flash_busaddr);
			if (!ha->flash_data){
				printk(KERN_WARNING "Unable to allocate a flash buffer\n");
				return IPS_FAILURE;
			}
			ha->flash_datasize = 0;
			ha->flash_len = datasize;
		} else
			return IPS_FAILURE;
	} else {
		if (pt->CoppCP.cmd.flashfw.count + ha->flash_datasize >
		    ha->flash_len) {
			ips_free_flash_copperhead(ha);
			IPS_PRINTK(KERN_WARNING, ha->pcidev,
				   "failed size sanity check\n");
			return IPS_FAILURE;
		}
	}
	if (!ha->flash_data)
		return IPS_FAILURE;
	pt->BasicStatus = 0;
	memcpy(&ha->flash_data[ha->flash_datasize], pt + 1,
	       pt->CoppCP.cmd.flashfw.count);
	ha->flash_datasize += pt->CoppCP.cmd.flashfw.count;
	if (pt->CoppCP.cmd.flashfw.packet_num ==
	    pt->CoppCP.cmd.flashfw.total_packets - 1) {
		if (pt->CoppCP.cmd.flashfw.type == IPS_BIOS_IMAGE)
			return ips_flash_bios(ha, pt, scb);
		else if (pt->CoppCP.cmd.flashfw.type == IPS_FW_IMAGE)
			return ips_flash_firmware(ha, pt, scb);
	}
	return IPS_SUCCESS_IMM;
}
