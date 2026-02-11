mon_new (gsize id)
{
	MonoThreadsSync *new_;

	if (!monitor_freelist) {
		MonitorArray *marray;
		int i;

		new_ = NULL;
		for (marray = monitor_allocated; marray; marray = marray->next) {
			for (i = 0; i < marray->num_monitors; ++i) {
				if (mono_gchandle_get_target ((guint32)marray->monitors [i].data) == NULL) {
					new_ = &marray->monitors [i];
					if (new_->wait_list) {

						while (new_->wait_list) {
							LOCK_DEBUG (g_message (G_GNUC_PRETTY_FUNCTION ": (%d): Closing orphaned event %d", mono_thread_info_get_small_id (), new->wait_list->data));
							CloseHandle (new_->wait_list->data);
							new_->wait_list = g_slist_remove (new_->wait_list, new_->wait_list->data);
						}
					}
					mono_gchandle_free ((guint32)new_->data);
					new_->data = monitor_freelist;
					monitor_freelist = new_;
				}
			}

			if (new_)
				break;
		}

		if (!monitor_freelist) {
			MonitorArray *last;
			LOCK_DEBUG (g_message ("%s: allocating more monitors: %d", __func__, array_size));
			marray = (MonitorArray *)g_malloc0 (MONO_SIZEOF_MONO_ARRAY + array_size * sizeof (MonoThreadsSync));
			marray->num_monitors = array_size;
			array_size *= 2;

			for (i = 0; i < marray->num_monitors - 1; ++i) {
				marray->monitors [i].data = &marray->monitors [i + 1];
			}
			marray->monitors [i].data = NULL;
			monitor_freelist = &marray->monitors [0];


			if (!monitor_allocated) {
				monitor_allocated = marray;
			} else {
				last = monitor_allocated;
				while (last->next)
					last = last->next;
				last->next = marray;
			}
		}
	}

	new_ = monitor_freelist;
	monitor_freelist = (MonoThreadsSync *)new_->data;

	new_->status = mon_status_set_owner (0, id);
	new_->status = mon_status_init_entry_count (new_->status);
	new_->nest = 1;
	new_->data = NULL;

#ifndef DISABLE_PERFCOUNTERS
	mono_perfcounters->gc_sync_blocks++;
#endif
	return new_;
}
