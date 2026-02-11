add_alarm (ECalComponent *comp,
           icalcomponent *alarm,
           const gchar *auid)
{
	ECalComponentPrivate *priv;
	icalcomponent *old_alarm;

	priv = comp->priv;


	old_alarm = g_hash_table_lookup (priv->alarm_uid_hash, auid);
	if (old_alarm != NULL) {
		gchar *new_auid;

		g_message ("add_alarm(): Got alarm with duplicated UID `%s', changing it...", auid);

		remove_alarm_uid (alarm);

		new_auid = e_cal_component_gen_uid ();
		auid = set_alarm_uid (alarm, new_auid);
		g_free (new_auid);
	}

	g_hash_table_insert (priv->alarm_uid_hash, (gchar *) auid, alarm);
	return auid;
}
