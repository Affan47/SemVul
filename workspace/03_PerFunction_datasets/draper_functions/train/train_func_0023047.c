update_stream_info (GthMediaViewerPage *self)
{
	GstElement *audio_sink;
	GstElement *video_sink;
	GstPad     *audio_pad;
	GstPad     *video_pad;

	g_object_get (self->priv->playbin,
		      "audio-sink", &audio_sink,
		      "video-sink", &video_sink,
		      NULL);

	if (audio_sink != NULL) {
		audio_pad = gst_element_get_static_pad (GST_ELEMENT (audio_sink), "sink");
		if (audio_pad != NULL)
			self->priv->has_audio = TRUE;
	}

	if (video_sink != NULL) {
		video_pad = gst_element_get_static_pad (GST_ELEMENT (video_sink), "sink");
		if (video_pad != NULL) {
			GstCaps *caps;

			self->priv->has_video = TRUE;

			if ((caps = gst_pad_get_current_caps (video_pad)) != NULL) {
				GstStructure *structure;
				int           video_width;
				int           video_height;

				structure = gst_caps_get_structure (caps, 0);
				gst_structure_get_fraction (structure, "framerate", &self->priv->video_fps_n, &self->priv->video_fps_d);
				gst_structure_get_int (structure, "width", &video_width);
				gst_structure_get_int (structure, "height", &video_height);

				g_file_info_set_attribute_int32 (self->priv->file_data->info, "frame::width", video_width);
				g_file_info_set_attribute_int32 (self->priv->file_data->info, "frame::height", video_height);

				gst_caps_unref (caps);
			}
		}
	}
}
