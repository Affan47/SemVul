scif_add_epd_to_zombie_list(struct scif_endpt *ep, bool eplock_held)
{
	if (!eplock_held)
		mutex_lock(&scif_info.eplock);
	spin_lock(&ep->lock);
	ep->state = SCIFEP_ZOMBIE;
	spin_unlock(&ep->lock);
	list_add_tail(&ep->list, &scif_info.zombie);
	scif_info.nr_zombies++;
	if (!eplock_held)
		mutex_unlock(&scif_info.eplock);
	schedule_work(&scif_info.misc_work);
}
