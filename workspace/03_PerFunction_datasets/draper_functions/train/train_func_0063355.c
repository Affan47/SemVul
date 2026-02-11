image_osd_free(OverlayStateData *osd)
{
	if (!osd) return;

	if (osd->idle_id) g_source_remove(osd->idle_id);
	if (osd->timer_id) g_source_remove(osd->timer_id);

	file_data_unregister_notify_func(image_osd_notify_cb, osd);

	if (osd->imd)
		{
		image_set_osd_data(osd->imd, NULL);
		g_signal_handler_disconnect(osd->imd->pr, osd->destroy_id);

		image_set_state_func(osd->imd, NULL, NULL);

		image_osd_info_hide(osd);
		image_osd_icons_hide(osd);
		}

	if (osd->histogram) histogram_free(osd->histogram);

	g_free(osd);
}
