qla2x00_async_adisc(struct scsi_qla_host *vha, fc_port_t *fcport,
    uint16_t *data)
{
	srb_t *sp;
	struct srb_iocb *lio;
	int rval;

	rval = QLA_FUNCTION_FAILED;
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp)
		goto done;

	sp->type = SRB_ADISC_CMD;
	sp->name = "adisc";
	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha) + 2);

	lio = &sp->u.iocb_cmd;
	lio->timeout = qla2x00_async_iocb_timeout;
	sp->done = qla2x00_async_adisc_sp_done;
	if (data[1] & QLA_LOGIO_LOGIN_RETRIED)
		lio->u.logio.flags |= SRB_LOGIN_RETRIED;
	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS)
		goto done_free_sp;

	ql_dbg(ql_dbg_disc, vha, 0x206f,
	    "Async-adisc - hdl=%x loopid=%x portid=%02x%02x%02x.\n",
	    sp->handle, fcport->loop_id, fcport->d_id.b.domain,
	    fcport->d_id.b.area, fcport->d_id.b.al_pa);
	return rval;

done_free_sp:
	sp->free(fcport->vha, sp);
done:
	return rval;
}
