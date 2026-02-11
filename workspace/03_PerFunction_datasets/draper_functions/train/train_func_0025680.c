tulip_main(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb;

	for (;;) {
		tulip_scsi(host);


		while ((scb = initio_find_done_scb(host)) != NULL) {
			if (scb->tastat == INI_QUEUE_FULL) {
				host->max_tags[scb->target] =
				    host->act_tags[scb->target] - 1;
				scb->tastat = 0;
				initio_append_pend_scb(host, scb);
				continue;
			}
			if (!(scb->mode & SCM_RSENS)) {
				if (scb->tastat == 2) {


					if (scb->flags & SCF_SENSE) {
						u8 len;
						len = scb->senselen;
						if (len == 0)
							len = 1;
						scb->buflen = scb->senselen;
						scb->bufptr = scb->senseptr;
						scb->flags &= ~(SCF_SG | SCF_DIR);


						scb->mode = SCM_RSENS;
						scb->ident &= 0xBF;
						scb->tagmsg = 0;
						scb->tastat = 0;
						scb->cdblen = 6;
						scb->cdb[0] = SCSICMD_RequestSense;
						scb->cdb[1] = 0;
						scb->cdb[2] = 0;
						scb->cdb[3] = 0;
						scb->cdb[4] = len;
						scb->cdb[5] = 0;
						initio_push_pend_scb(host, scb);
						break;
					}
				}
			} else {

				if (scb->tastat == 2) {

					scb->hastat = HOST_BAD_PHAS;
				}
				scb->tastat = 2;
			}
			scb->flags |= SCF_DONE;
			if (scb->flags & SCF_POST) {

				(*scb->post) ((u8 *) host, (u8 *) scb);
			}
		}

		if (inb(host->addr + TUL_SStatus0) & TSS_INT_PENDING)
			continue;
		if (host->active)
			return 1;

		if (initio_find_first_pend_scb(host) == NULL)
			return 1;
	}

}
