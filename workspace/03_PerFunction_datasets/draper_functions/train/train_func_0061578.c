qla4xxx_set_port_state(struct Scsi_Host *shost)
{
	struct scsi_qla_host *ha = to_qla_host(shost);
	struct iscsi_cls_host *ihost = shost->shost_data;
	uint32_t state = ISCSI_PORT_STATE_DOWN;

	if (test_bit(AF_LINK_UP, &ha->flags))
		state = ISCSI_PORT_STATE_UP;

	ihost->port_state = state;
}
