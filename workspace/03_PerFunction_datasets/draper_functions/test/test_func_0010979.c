zeitgeist_monitor_manager_notify_delete (ZeitgeistMonitorManager* self, ZeitgeistTimeRange* time_range, guint32* event_ids, int event_ids_length1) {
	GHashTable* _tmp0_ = NULL;
	GList* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (time_range != NULL);
	_tmp0_ = self->priv->monitors;
	_tmp1_ = g_hash_table_get_values (_tmp0_);
	{
		GList* mon_collection = NULL;
		GList* mon_it = NULL;
		mon_collection = _tmp1_;
		for (mon_it = mon_collection; mon_it != NULL; mon_it = mon_it->next) {
			ZeitgeistMonitorManagerMonitor* mon = NULL;
			mon = (ZeitgeistMonitorManagerMonitor*) mon_it->data;
			{
				ZeitgeistMonitorManagerMonitor* _tmp2_ = NULL;
				ZeitgeistTimeRange* _tmp3_ = NULL;
				guint32* _tmp4_ = NULL;
				gint _tmp4__length1 = 0;
				_tmp2_ = mon;
				_tmp3_ = time_range;
				_tmp4_ = event_ids;
				_tmp4__length1 = event_ids_length1;
				zeitgeist_monitor_manager_monitor_notify_delete (_tmp2_, _tmp3_, _tmp4_, _tmp4__length1);
			}
		}
		_g_list_free0 (mon_collection);
	}
}
