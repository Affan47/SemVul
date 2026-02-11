ahc_freeze_untagged_queues(struct ahc_softc *ahc)
{
	if ((ahc->flags & AHC_SCB_BTT) == 0)
		ahc->untagged_queue_lock++;
}
