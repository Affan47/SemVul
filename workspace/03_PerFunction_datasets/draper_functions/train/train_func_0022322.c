gst_binding_load_video_info (gstPlay *play) {
	if (!isValid (play)) return FALSE;

	GList *stream_info = NULL, *stream;
	g_object_get (G_OBJECT (play->element), "stream-info", &stream_info, NULL);
	if (!stream_info) return FALSE;


	if (play->video_info == NULL) {
		play->video_info = g_new0 (gstVideoInfo, 1);
	}


	play->video_info->has_video = gst_binding_has_video(play);
	play->video_info->has_audio = gst_binding_has_audio(play);


	if (!play->video_info->has_video)
		return play->video_info->has_audio;


  	for (stream = stream_info; stream; stream = g_list_next (stream)) {
  		GObject *stream_data = G_OBJECT (stream->data);
  		gint stream_type;
	    g_object_get (stream_data, "type", &stream_type, NULL);


 		if (stream_type == 2) {
	  		GstObject *stream_object;
	    	g_object_get (stream_data, "object", &stream_object, NULL);

			GstCaps *caps;
			g_object_get(stream_object, "caps", &caps, NULL);
			if (!GST_IS_CAPS(caps)) return FALSE;

			gint caps_count = gst_caps_get_size (caps), caps_index;
			GstStructure *caps_struct;
			const GValue *caps_value;
			gint caps_width = -1, caps_height = -1;
			gfloat caps_frame_rate = -1;
			for (caps_index = 0; caps_index < caps_count; caps_index++) {
    			caps_struct = gst_caps_get_structure (caps, caps_index);


    			const gchar *mime_type;
				mime_type = gst_structure_get_name (caps_struct);
				if ((!mime_type) || (g_ascii_strncasecmp(mime_type, "video", 5)))
					continue;


				caps_value = gst_structure_get_value (caps_struct, "width");
    			if (caps_value && (G_VALUE_TYPE (caps_value) == G_TYPE_INT))
    				caps_width = g_value_get_int(caps_value);


    			caps_value = gst_structure_get_value (caps_struct, "height");
    			if (caps_value && (G_VALUE_TYPE (caps_value) == G_TYPE_INT))
    				caps_height = g_value_get_int(caps_value);


    			caps_value = gst_structure_get_value (caps_struct, "framerate");
    			if (caps_value && (G_VALUE_TYPE (caps_value) == GST_TYPE_FRACTION)) {
    				int num = caps_value->data[0].v_int, den = caps_value->data[1].v_int;
		            caps_frame_rate = (float)num/den;
				}
			}

			if ((caps_width != -1) && (caps_height != -1) && (caps_frame_rate != -1)) {
				play->video_info->width = caps_width;
				play->video_info->height = caps_height;
				play->video_info->aspect_ratio = ((float)caps_width)/((float)caps_height);
				play->video_info->frame_rate = caps_frame_rate;
				return TRUE;
			}
		}
	}
	return FALSE;
}
