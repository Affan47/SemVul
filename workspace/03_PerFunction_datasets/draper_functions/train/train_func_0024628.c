ahc_search_untagged_queues(struct ahc_softc *ahc, ahc_io_ctx_t ctx,
			   int target, char channel, int lun, uint32_t status,
			   ahc_search_action action)
{
	struct	scb *scb;
	int	maxtarget;
	int	found;
	int	i;

	if (action == SEARCH_COMPLETE) {


		ahc_freeze_untagged_queues(ahc);
	}

	found = 0;
	i = 0;
	if ((ahc->flags & AHC_SCB_BTT) == 0) {

		maxtarget = 16;
		if (target != CAM_TARGET_WILDCARD) {

			i = target;
			if (channel == 'B')
				i += 8;
			maxtarget = i + 1;
		}
	} else {
		maxtarget = 0;
	}

	for (; i < maxtarget; i++) {
		struct scb_tailq *untagged_q;
		struct scb *next_scb;

		untagged_q = &(ahc->untagged_queues[i]);
		next_scb = TAILQ_FIRST(untagged_q);
		while (next_scb != NULL) {

			scb = next_scb;
			next_scb = TAILQ_NEXT(scb, links.tqe);


			if ((scb->flags & SCB_ACTIVE) != 0)
				continue;

			if (ahc_match_scb(ahc, scb, target, channel, lun,
					  SCB_LIST_NULL, ROLE_INITIATOR) == 0
			 || (ctx != NULL && ctx != scb->io_ctx))
				continue;


			found++;
			switch (action) {
			case SEARCH_COMPLETE:
			{
				cam_status ostat;
				cam_status cstat;

				ostat = ahc_get_transaction_status(scb);
				if (ostat == CAM_REQ_INPROG)
					ahc_set_transaction_status(scb, status);
				cstat = ahc_get_transaction_status(scb);
				if (cstat != CAM_REQ_CMP)
					ahc_freeze_scb(scb);
				if ((scb->flags & SCB_ACTIVE) == 0)
					printk("Inactive SCB in untaggedQ\n");
				ahc_done(ahc, scb);
				break;
			}
			case SEARCH_REMOVE:
				scb->flags &= ~SCB_UNTAGGEDQ;
				TAILQ_REMOVE(untagged_q, scb, links.tqe);
				break;
			case SEARCH_COUNT:
				break;
			}
		}
	}

	if (action == SEARCH_COMPLETE)
		ahc_release_untagged_queues(ahc);
	return (found);
}
