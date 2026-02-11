getSupportedFormats(GnashWebcam *cam, GstCaps *caps)
{
    gint i;
    gint num_structs;

    num_structs = gst_caps_get_size (caps);

    for (i=0; i < num_structs; i++) {
        GstStructure *structure;
        const GValue *width, *height;


        structure = gst_caps_get_structure (caps, i);


        if (!gst_structure_has_name (structure, "video/x-raw-yuv") &&
            !gst_structure_has_name (structure, "video/x-raw-rgb"))
        {
          continue;
        }

        width  = gst_structure_get_value (structure, "width");
        height = gst_structure_get_value (structure, "height");

        if (G_VALUE_HOLDS_INT (const_cast<GValue *>(width))) {
              WebcamVidFormat video_format;

              video_format.mimetype =
                g_strdup (gst_structure_get_name (structure));
              gst_structure_get_int (structure, "width", &(video_format.width));
              gst_structure_get_int (structure, "height", &(video_format.height));
              addSupportedFormat(cam, &video_format, structure);
        }
        else if (GST_VALUE_HOLDS_INT_RANGE (const_cast<GValue *>(width))) {
            int min_width, max_width, min_height, max_height;
            int cur_width, cur_height;

            min_width  = gst_value_get_int_range_min (width);
            max_width  = gst_value_get_int_range_max (width);
            min_height = gst_value_get_int_range_min (height);
            max_height = gst_value_get_int_range_max (height);

            cur_width  = min_width;
            cur_height = min_height;
            while (cur_width <= max_width && cur_height <= max_height) {
                WebcamVidFormat video_format;

                video_format.mimetype =
                    g_strdup (gst_structure_get_name (structure));
                video_format.width    = cur_width;
                video_format.height   = cur_height;
                addSupportedFormat(cam, &video_format, structure);
                cur_width  *= 2;
                cur_height *= 2;
            }

            cur_width  = max_width;
            cur_height = max_height;
            while (cur_width > min_width && cur_height > min_height) {
                WebcamVidFormat video_format;

                video_format.mimetype =
                    g_strdup (gst_structure_get_name (structure));
                video_format.width    = cur_width;
                video_format.height   = cur_height;
                addSupportedFormat(cam, &video_format, structure);
                cur_width  /= 2;
                cur_height /= 2;
            }
        }
        else {
            log_error(_("%s: type %s, cannot be handled for resolution width"),
                __FUNCTION__, G_VALUE_TYPE_NAME (const_cast<GValue *>(width)));
        }
    }
}
