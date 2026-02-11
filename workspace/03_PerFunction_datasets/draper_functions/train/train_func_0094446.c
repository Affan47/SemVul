gdm_wimax_event_exit(void)
{
	if (wm_event.sock && --wm_event.ref_cnt == 0) {
		struct evt_entry *e, *temp;
		unsigned long flags;

		spin_lock_irqsave(&wm_event.evt_lock, flags);

		list_for_each_entry_safe(e, temp, &wm_event.evtq, list) {
			list_del(&e->list);
			free_event_entry(e);
		}
		list_for_each_entry_safe(e, temp, &wm_event.freeq, list) {
			list_del(&e->list);
			free_event_entry(e);
		}

		spin_unlock_irqrestore(&wm_event.evt_lock, flags);
		netlink_exit(wm_event.sock);
		wm_event.sock = NULL;
	}
}
