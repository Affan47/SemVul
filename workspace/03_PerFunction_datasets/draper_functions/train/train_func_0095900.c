ips_usrcmd(ips_ha_t * ha, ips_passthru_t * pt, ips_scb_t * scb)
{
	IPS_SG_LIST sg_list;
	uint32_t cmd_busaddr;

	METHOD_TRACE("ips_usrcmd", 1);

	if ((!scb) || (!pt) || (!ha))
		return (0);


	sg_list.list = scb->sg_list.list;
	cmd_busaddr = scb->scb_busaddr;

	memcpy(&scb->cmd, &pt->CoppCP.cmd, sizeof (IPS_IOCTL_CMD));
	memcpy(&scb->dcdb, &pt->CoppCP.dcdb, sizeof (IPS_DCDB_TABLE));


	scb->sg_list.list = sg_list.list;
	scb->scb_busaddr = cmd_busaddr;
	scb->bus = scb->scsi_cmd->device->channel;
	scb->target_id = scb->scsi_cmd->device->id;
	scb->lun = scb->scsi_cmd->device->lun;
	scb->sg_len = 0;
	scb->data_len = 0;
	scb->flags = 0;
	scb->op_code = 0;
	scb->callback = ipsintr_done;
	scb->timeout = ips_cmd_timeout;
	scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);


	if ((scb->cmd.basic_io.op_code == IPS_CMD_READ_SG) ||
	    (scb->cmd.basic_io.op_code == IPS_CMD_WRITE_SG) ||
	    (scb->cmd.basic_io.op_code == IPS_CMD_DCDB_SG))
		return (0);

	if (pt->CmdBSize) {
		scb->data_len = pt->CmdBSize;
		scb->data_busaddr = ha->ioctl_busaddr + sizeof (ips_passthru_t);
	} else {
		scb->data_busaddr = 0L;
	}

	if (scb->cmd.dcdb.op_code == IPS_CMD_DCDB)
		scb->cmd.dcdb.dcdb_address = cpu_to_le32(scb->scb_busaddr +
							 (unsigned long) &scb->
							 dcdb -
							 (unsigned long) scb);

	if (pt->CmdBSize) {
		if (scb->cmd.dcdb.op_code == IPS_CMD_DCDB)
			scb->dcdb.buffer_pointer =
			    cpu_to_le32(scb->data_busaddr);
		else
			scb->cmd.basic_io.sg_addr =
			    cpu_to_le32(scb->data_busaddr);
	}


	if (pt->TimeOut) {
		scb->timeout = pt->TimeOut;

		if (pt->TimeOut <= 10)
			scb->dcdb.cmd_attribute |= IPS_TIMEOUT10;
		else if (pt->TimeOut <= 60)
			scb->dcdb.cmd_attribute |= IPS_TIMEOUT60;
		else
			scb->dcdb.cmd_attribute |= IPS_TIMEOUT20M;
	}


	scb->scsi_cmd->result = DID_OK << 16;


	return (1);
}
