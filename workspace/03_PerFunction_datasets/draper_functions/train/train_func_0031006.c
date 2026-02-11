ahd_linux_set_qas(struct scsi_target *starget, int qas)
{
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	struct ahd_softc *ahd = *((struct ahd_softc **)shost->hostdata);
	struct ahd_tmode_tstate *tstate;
	struct ahd_initiator_tinfo *tinfo
		= ahd_fetch_transinfo(ahd,
				      starget->channel + 'A',
				      shost->this_id, starget->id, &tstate);
	struct ahd_devinfo devinfo;
	unsigned int ppr_options = tinfo->goal.ppr_options
		& ~MSG_EXT_PPR_QAS_REQ;
	unsigned int period = tinfo->goal.period;
	unsigned int dt;
	unsigned long flags;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		printk("%s: %s QAS\n", ahd_name(ahd),
		       qas ? "enabling" : "disabling");
#endif

	if (qas) {
		ppr_options |= MSG_EXT_PPR_QAS_REQ;
	}

	dt = ppr_options & MSG_EXT_PPR_DT_REQ;

	ahd_compile_devinfo(&devinfo, shost->this_id, starget->id, 0,
			    starget->channel + 'A', ROLE_INITIATOR);
	ahd_find_syncrate(ahd, &period, &ppr_options,
			  dt ? AHD_SYNCRATE_MAX : AHD_SYNCRATE_ULTRA2);

	ahd_lock(ahd, &flags);
	ahd_set_syncrate(ahd, &devinfo, period, tinfo->goal.offset,
			 ppr_options, AHD_TRANS_GOAL, FALSE);
	ahd_unlock(ahd, &flags);
}
