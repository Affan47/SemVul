ahc_build_transfer_msg(struct ahc_softc *ahc, struct ahc_devinfo *devinfo)
{


	struct	ahc_initiator_tinfo *tinfo;
	struct	ahc_tmode_tstate *tstate;
	const struct ahc_syncrate *rate;
	int	dowide;
	int	dosync;
	int	doppr;
	u_int	period;
	u_int	ppr_options;
	u_int	offset;

	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);


	period = tinfo->goal.period;
	offset = tinfo->goal.offset;
	ppr_options = tinfo->goal.ppr_options;

	if (devinfo->role == ROLE_TARGET)
		ppr_options = 0;
	rate = ahc_devlimited_syncrate(ahc, tinfo, &period,
				       &ppr_options, devinfo->role);
	dowide = tinfo->curr.width != tinfo->goal.width;
	dosync = tinfo->curr.offset != offset || tinfo->curr.period != period;


	doppr = ppr_options != 0;

	if (!dowide && !dosync && !doppr) {
		dowide = tinfo->goal.width != MSG_EXT_WDTR_BUS_8_BIT;
		dosync = tinfo->goal.offset != 0;
	}

	if (!dowide && !dosync && !doppr) {


		if ((ahc->features & AHC_WIDE) != 0)
			dowide = 1;
		else
			dosync = 1;

		if (bootverbose) {
			ahc_print_devinfo(ahc, devinfo);
			printk("Ensuring async\n");
		}
	}


	if (devinfo->role == ROLE_TARGET)
		doppr = 0;


	if (doppr || (dosync && !dowide)) {

		offset = tinfo->goal.offset;
		ahc_validate_offset(ahc, tinfo, rate, &offset,
				    doppr ? tinfo->goal.width
					  : tinfo->curr.width,
				    devinfo->role);
		if (doppr) {
			ahc_construct_ppr(ahc, devinfo, period, offset,
					  tinfo->goal.width, ppr_options);
		} else {
			ahc_construct_sdtr(ahc, devinfo, period, offset);
		}
	} else {
		ahc_construct_wdtr(ahc, devinfo, tinfo->goal.width);
	}
}
