raise_barrier(struct r1conf *conf, sector_t sector_nr)
{
	spin_lock_irq(&conf->resync_lock);


	wait_event_lock_irq(conf->wait_barrier, !conf->nr_waiting,
			    conf->resync_lock);


	conf->barrier++;
	conf->next_resync = sector_nr;


	wait_event_lock_irq(conf->wait_barrier,
			    !conf->array_frozen &&
			    conf->barrier < RESYNC_DEPTH &&
			    conf->current_window_requests == 0 &&
			    (conf->start_next_window >=
			     conf->next_resync + RESYNC_SECTORS),
			    conf->resync_lock);

	conf->nr_pending++;
	spin_unlock_irq(&conf->resync_lock);
}
