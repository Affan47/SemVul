pvr2_context_set_notify(struct pvr2_context *mp, int fl)
{
	int signal_flag = 0;
	mutex_lock(&pvr2_context_mutex);
	if (fl) {
		if (!mp->notify_flag) {
			signal_flag = (pvr2_context_notify_first == NULL);
			mp->notify_prev = pvr2_context_notify_last;
			mp->notify_next = NULL;
			pvr2_context_notify_last = mp;
			if (mp->notify_prev) {
				mp->notify_prev->notify_next = mp;
			} else {
				pvr2_context_notify_first = mp;
			}
			mp->notify_flag = !0;
		}
	} else {
		if (mp->notify_flag) {
			mp->notify_flag = 0;
			if (mp->notify_next) {
				mp->notify_next->notify_prev = mp->notify_prev;
			} else {
				pvr2_context_notify_last = mp->notify_prev;
			}
			if (mp->notify_prev) {
				mp->notify_prev->notify_next = mp->notify_next;
			} else {
				pvr2_context_notify_first = mp->notify_next;
			}
		}
	}
	mutex_unlock(&pvr2_context_mutex);
	if (signal_flag) wake_up(&pvr2_context_sync_data);
}
