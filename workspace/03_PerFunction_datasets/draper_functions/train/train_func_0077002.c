qla1280_marker(struct scsi_qla_host *ha, int bus, int id, int lun, u8 type)
{
	struct mrk_entry *pkt;

	ENTER("qla1280_marker");


	if ((pkt = (struct mrk_entry *) qla1280_req_pkt(ha))) {
		pkt->entry_type = MARKER_TYPE;
		pkt->lun = (uint8_t) lun;
		pkt->target = (uint8_t) (bus ? (id | BIT_7) : id);
		pkt->modifier = type;
		pkt->entry_status = 0;


		qla1280_isp_cmd(ha);
	}

	LEAVE("qla1280_marker");
}
