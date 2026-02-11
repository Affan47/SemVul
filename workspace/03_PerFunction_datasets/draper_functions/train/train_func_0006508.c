brasero_track_image_cfg_get_info_cb (GObject *object,
				     GAsyncResult *result,
				     gpointer user_data)
{
	BraseroTrackImageInfo *info;
	BraseroTrackImageCfgPrivate *priv;

	priv = BRASERO_TRACK_IMAGE_CFG_PRIVATE (object);

	info = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (result));
	if (priv->cancel == info->cancel) {
		g_object_unref (priv->cancel);
		priv->cancel = NULL;
	}

	if (g_cancellable_is_cancelled (info->cancel)) {
		brasero_track_changed (BRASERO_TRACK (object));
		return;
	}

	if (info->format == BRASERO_IMAGE_FORMAT_NONE
	||  info->blocks == 0) {
		GError *error = NULL;

		g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (result), &error);
		priv->error = error;

		brasero_track_changed (BRASERO_TRACK (object));
		return;
	}

	brasero_track_image_cfg_set_uri (BRASERO_TRACK_IMAGE_CFG (object),
	                                 info->uri,
	                                 priv->format != BRASERO_IMAGE_FORMAT_NONE? priv->format:info->format);

	BRASERO_TRACK_IMAGE_CLASS (brasero_track_image_cfg_parent_class)->set_block_num (BRASERO_TRACK_IMAGE (object), info->blocks);
	brasero_track_changed (BRASERO_TRACK (object));
}
