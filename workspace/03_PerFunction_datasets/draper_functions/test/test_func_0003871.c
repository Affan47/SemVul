ahd_abort_scbs(struct ahd_softc *ahd, int target, char channel,
	       int lun, u_int tag, role_t role, uint32_t status)
{
	struct		scb *scbp;
	struct		scb *scbp_next;
	u_int		i, j;
	u_int		maxtarget;
	u_int		minlun;
	u_int		maxlun;
	int		found;
	ahd_mode_state	saved_modes;


	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	found = ahd_search_qinfifo(ahd, target, channel, lun, SCB_LIST_NULL,
				   role, CAM_REQUEUE_REQ, SEARCH_COMPLETE);


	i = 0;
	maxtarget = 16;
	if (target != CAM_TARGET_WILDCARD) {
		i = target;
		if (channel == 'B')
			i += 8;
		maxtarget = i + 1;
	}

	if (lun == CAM_LUN_WILDCARD) {
		minlun = 0;
		maxlun = AHD_NUM_LUNS_NONPKT;
	} else if (lun >= AHD_NUM_LUNS_NONPKT) {
		minlun = maxlun = 0;
	} else {
		minlun = lun;
		maxlun = lun + 1;
	}

	if (role != ROLE_TARGET) {
		for (;i < maxtarget; i++) {
			for (j = minlun;j < maxlun; j++) {
				u_int scbid;
				u_int tcl;

				tcl = BUILD_TCL_RAW(i, 'A', j);
				scbid = ahd_find_busy_tcl(ahd, tcl);
				scbp = ahd_lookup_scb(ahd, scbid);
				if (scbp == NULL
				 || ahd_match_scb(ahd, scbp, target, channel,
						  lun, tag, role) == 0)
					continue;
				ahd_unbusy_tcl(ahd, BUILD_TCL_RAW(i, 'A', j));
			}
		}
	}


	ahd_flush_qoutfifo(ahd);


	scbp_next = LIST_FIRST(&ahd->pending_scbs);
	while (scbp_next != NULL) {
		scbp = scbp_next;
		scbp_next = LIST_NEXT(scbp, pending_links);
		if (ahd_match_scb(ahd, scbp, target, channel, lun, tag, role)) {
			cam_status ostat;

			ostat = ahd_get_transaction_status(scbp);
			if (ostat == CAM_REQ_INPROG)
				ahd_set_transaction_status(scbp, status);
			if (ahd_get_transaction_status(scbp) != CAM_REQ_CMP)
				ahd_freeze_scb(scbp);
			if ((scbp->flags & SCB_ACTIVE) == 0)
				printk("Inactive SCB on pending list\n");
			ahd_done(ahd, scbp);
			found++;
		}
	}
	ahd_restore_modes(ahd, saved_modes);
	ahd_platform_abort_scbs(ahd, target, channel, lun, tag, role, status);
	ahd->flags |= AHD_UPDATE_PEND_CMDS;
	return found;
}
