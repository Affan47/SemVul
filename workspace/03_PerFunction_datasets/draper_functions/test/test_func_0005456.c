tcm_loop_submission_work(struct work_struct *work)
{
	struct tcm_loop_cmd *tl_cmd =
		container_of(work, struct tcm_loop_cmd, work);
	struct se_cmd *se_cmd = &tl_cmd->tl_se_cmd;
	struct scsi_cmnd *sc = tl_cmd->sc;
	struct tcm_loop_nexus *tl_nexus;
	struct tcm_loop_hba *tl_hba;
	struct tcm_loop_tpg *tl_tpg;
	struct scatterlist *sgl_bidi = NULL;
	u32 sgl_bidi_count = 0, transfer_length;
	int rc;

	tl_hba = *(struct tcm_loop_hba **)shost_priv(sc->device->host);
	tl_tpg = &tl_hba->tl_hba_tpgs[sc->device->id];


	if (!tl_tpg->tl_hba) {
		set_host_byte(sc, DID_NO_CONNECT);
		goto out_done;
	}
	if (tl_tpg->tl_transport_status == TCM_TRANSPORT_OFFLINE) {
		set_host_byte(sc, DID_TRANSPORT_DISRUPTED);
		goto out_done;
	}
	tl_nexus = tl_tpg->tl_nexus;
	if (!tl_nexus) {
		scmd_printk(KERN_ERR, sc, "TCM_Loop I_T Nexus"
				" does not exist\n");
		set_host_byte(sc, DID_ERROR);
		goto out_done;
	}
	if (scsi_bidi_cmnd(sc)) {
		struct scsi_data_buffer *sdb = scsi_in(sc);

		sgl_bidi = sdb->table.sgl;
		sgl_bidi_count = sdb->table.nents;
		se_cmd->se_cmd_flags |= SCF_BIDI;

	}

	transfer_length = scsi_transfer_length(sc);
	if (!scsi_prot_sg_count(sc) &&
	    scsi_get_prot_op(sc) != SCSI_PROT_NORMAL) {
		se_cmd->prot_pto = true;


		transfer_length = scsi_bufflen(sc);
	}

	se_cmd->tag = tl_cmd->sc_cmd_tag;
	rc = target_submit_cmd_map_sgls(se_cmd, tl_nexus->se_sess, sc->cmnd,
			&tl_cmd->tl_sense_buf[0], tl_cmd->sc->device->lun,
			transfer_length, TCM_SIMPLE_TAG,
			sc->sc_data_direction, 0,
			scsi_sglist(sc), scsi_sg_count(sc),
			sgl_bidi, sgl_bidi_count,
			scsi_prot_sglist(sc), scsi_prot_sg_count(sc));
	if (rc < 0) {
		set_host_byte(sc, DID_NO_CONNECT);
		goto out_done;
	}
	return;

out_done:
	kmem_cache_free(tcm_loop_cmd_cache, tl_cmd);
	sc->scsi_done(sc);
	return;
}
