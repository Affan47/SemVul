gst_face_overlay_message_handler (GstBin * bin, GstMessage * message)
{
  if (GST_MESSAGE_TYPE (message) == GST_MESSAGE_ELEMENT &&
      strcmp (gst_structure_get_name (message->structure), "facedetect") == 0) {
    GstFaceOverlay *filter = GST_FACEOVERLAY (bin);


    guint x, y, width, height;
    int delta_x, delta_y, svg_x, svg_y, svg_width, svg_height;
    const GstStructure *face;
    int face_count;

    face_count =
        gst_value_list_get_size (gst_structure_get_value (message->structure,
            "faces"));


    face =
        gst_value_get_structure (gst_value_list_get_value
        (gst_structure_get_value (message->structure, "faces"),
            face_count - 1));
    gst_structure_get_uint (face, "x", &x);
    gst_structure_get_uint (face, "y", &y);
    gst_structure_get_uint (face, "width", &width);
    gst_structure_get_uint (face, "height", &height);


    delta_x = (int) (filter->x * (int) width);
    svg_x = (int) x + delta_x;

    delta_y = (int) (filter->y * (int) height);
    svg_y = (int) y + delta_y;

    svg_width = (int) width *filter->w;
    svg_height = (int) height *filter->h;

    g_object_set (filter->svg_overlay,
        "location", filter->location,
        "x", svg_x, "y", svg_y, "width", svg_width, "height", svg_height, NULL);

  }

  GST_BIN_CLASS (parent_class)->handle_message (bin, message);
}
