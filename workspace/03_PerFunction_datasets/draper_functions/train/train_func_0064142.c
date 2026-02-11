card_resume(struct pnp_dev *dev)
{
	struct pnp_card_link *link = dev->card_link;

	if (link->pm_state.event == PM_EVENT_ON)
		return 0;
	link->pm_state = PMSG_ON;
	link->driver->resume(link);
	return 0;
}
