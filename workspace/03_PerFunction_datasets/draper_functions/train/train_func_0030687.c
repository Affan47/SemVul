clocks_alarm_setup_dialog_finalize (GObject* obj) {
	ClocksAlarmSetupDialog * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, CLOCKS_ALARM_TYPE_SETUP_DIALOG, ClocksAlarmSetupDialog);
	_g_object_unref0 (self->priv->time_grid);
	_g_object_unref0 (self->priv->h_spinbutton);
	_g_object_unref0 (self->priv->m_spinbutton);
	_g_object_unref0 (self->priv->name_entry);
	_g_object_unref0 (self->priv->am_pm_button);
	self->priv->day_buttons = (_vala_array_free (self->priv->day_buttons, self->priv->day_buttons_length1, (GDestroyNotify) g_object_unref), NULL);
	_g_object_unref0 (self->priv->active_switch);
	_g_object_unref0 (self->priv->day_buttons_box);
	_g_object_unref0 (self->priv->am_pm_alignment);
	_g_object_unref0 (self->priv->am_pm_sizegroup);
	G_OBJECT_CLASS (clocks_alarm_setup_dialog_parent_class)->finalize (obj);
}
