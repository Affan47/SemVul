gmpc_provider_chart_lyrics_prop_free (GmpcProviderChartLyricsProp* self) {
	_mpd_freeSong0 (self->song);
	_g_object_unref0 (self->this);
	(self->callback_target_destroy_notify == NULL) ? NULL : (self->callback_target_destroy_notify (self->callback_target), NULL);
	self->callback = NULL;
	self->callback_target = NULL;
	self->callback_target_destroy_notify = NULL;
	__g_list_free__meta_data_free0_0 (self->list);
	g_slice_free (GmpcProviderChartLyricsProp, self);
}
