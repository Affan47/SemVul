sym_wide_nego(struct sym_hcb *np, struct sym_tcb *tp, struct sym_ccb *cp)
{
	int req = 1;
	int result;


	if (INB(np, HS_PRT) == HS_NEGOTIATE) {
		OUTB(np, HS_PRT, HS_BUSY);
		if (cp->nego_status && cp->nego_status != NS_WIDE)
			goto reject_it;
		req = 0;
	}


	result = sym_wide_nego_check(np, req, cp);
	if (result)
		goto reject_it;
	if (req) {
		cp->nego_status = NS_WIDE;
		OUTL_DSP(np, SCRIPTB_BA(np, wdtr_resp));
	} else {


		if (tp->tgoal.offset) {
			spi_populate_sync_msg(np->msgout, tp->tgoal.period,
					tp->tgoal.offset);

			if (DEBUG_FLAGS & DEBUG_NEGO) {
				sym_print_nego_msg(np, cp->target,
				                   "sync msgout", np->msgout);
			}

			cp->nego_status = NS_SYNC;
			OUTB(np, HS_PRT, HS_NEGOTIATE);
			OUTL_DSP(np, SCRIPTB_BA(np, sdtr_resp));
			return;
		} else
			OUTL_DSP(np, SCRIPTA_BA(np, clrack));
	}

	return;

reject_it:
	OUTL_DSP(np, SCRIPTB_BA(np, msg_bad));
}
