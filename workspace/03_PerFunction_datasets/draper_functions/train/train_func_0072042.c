ips_init_scb(ips_ha_t * ha, ips_scb_t * scb)
{
	IPS_SG_LIST sg_list;
	uint32_t cmd_busaddr, sg_busaddr;
	METHOD_TRACE("ips_init_scb", 1);

	if (scb == NULL)
		return;

	sg_list.list = scb->sg_list.list;
	cmd_busaddr = scb->scb_busaddr;
	sg_busaddr = scb->sg_busaddr;

	memset(scb, 0, sizeof (ips_scb_t));
	memset(ha->dummy, 0, sizeof (IPS_IO_CMD));


	ha->dummy->op_code = 0xFF;
	ha->dummy->ccsar = cpu_to_le32(ha->adapt->hw_status_start
				       + sizeof (IPS_ADAPTER));
	ha->dummy->command_id = IPS_MAX_CMDS;


	scb->scb_busaddr = cmd_busaddr;
	scb->sg_busaddr = sg_busaddr;
	scb->sg_list.list = sg_list.list;


	scb->cmd.basic_io.cccr = cpu_to_le32((uint32_t) IPS_BIT_ILE);
	scb->cmd.basic_io.ccsar = cpu_to_le32(ha->adapt->hw_status_start
					      + sizeof (IPS_ADAPTER));
}
