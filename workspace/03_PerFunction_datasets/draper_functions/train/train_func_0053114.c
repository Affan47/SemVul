gst_a2dp_sink_remove_fakesink(GstA2dpSink *self)
{
	g_mutex_lock(self->cb_mutex);

	if (self->fakesink != NULL) {
		gst_element_set_locked_state(self->fakesink, TRUE);
		gst_element_set_state(self->fakesink, GST_STATE_NULL);

		gst_bin_remove(GST_BIN(self), self->fakesink);
		self->fakesink = NULL;
	}

	g_mutex_unlock(self->cb_mutex);

	return TRUE;
}
