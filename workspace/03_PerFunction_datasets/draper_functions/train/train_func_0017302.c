gst_gdk_pixbuf_flush (GstGdkPixbuf * filter)
{
  GstBuffer *outbuf;
  GdkPixbuf *pixbuf;
  int y;
  guint8 *out_pix;
  guint8 *in_pix;
  int in_rowstride;
  GstFlowReturn ret;
  GstCaps *caps = NULL;
  gint n_channels;

  pixbuf = gdk_pixbuf_loader_get_pixbuf (filter->pixbuf_loader);
  if (pixbuf == NULL)
    goto no_pixbuf;

  if (filter->image_size == 0) {
    filter->width = gdk_pixbuf_get_width (pixbuf);
    filter->height = gdk_pixbuf_get_height (pixbuf);
    filter->rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    filter->image_size = filter->rowstride * filter->height;

    n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    switch (n_channels) {
      case 3:
        caps = gst_caps_from_string (GST_VIDEO_CAPS_RGB);
        break;
      case 4:
        caps = gst_caps_from_string (GST_VIDEO_CAPS_RGBA);
        break;
      default:
        goto channels_not_supported;
    }

    gst_caps_set_simple (caps,
        "width", G_TYPE_INT, filter->width,
        "height", G_TYPE_INT, filter->height,
        "framerate", GST_TYPE_FRACTION, filter->framerate_numerator,
        filter->framerate_denominator, NULL);

    GST_DEBUG ("Set size to %dx%d", filter->width, filter->height);
    gst_pad_set_caps (filter->srcpad, caps);
    gst_caps_unref (caps);
  }

  ret = gst_pad_alloc_buffer_and_set_caps (filter->srcpad,
      GST_BUFFER_OFFSET_NONE,
      filter->image_size, GST_PAD_CAPS (filter->srcpad), &outbuf);

  if (ret != GST_FLOW_OK)
    goto no_buffer;

  GST_BUFFER_TIMESTAMP (outbuf) = filter->last_timestamp;
  GST_BUFFER_DURATION (outbuf) = GST_CLOCK_TIME_NONE;

  in_pix = gdk_pixbuf_get_pixels (pixbuf);
  in_rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  out_pix = GST_BUFFER_DATA (outbuf);


  for (y = 0; y < filter->height; y++) {
    memcpy (out_pix, in_pix, filter->rowstride);
    in_pix += in_rowstride;
    out_pix += filter->rowstride;
  }

  GST_DEBUG ("pushing... %d bytes", GST_BUFFER_SIZE (outbuf));
  ret = gst_pad_push (filter->srcpad, outbuf);

  if (ret != GST_FLOW_OK)
    GST_DEBUG_OBJECT (filter, "flow: %s", gst_flow_get_name (ret));

  return ret;


no_pixbuf:
  {
    GST_ELEMENT_ERROR (filter, STREAM, DECODE, (NULL), ("error geting pixbuf"));
    return GST_FLOW_ERROR;
  }
channels_not_supported:
  {
    GST_ELEMENT_ERROR (filter, STREAM, DECODE, (NULL),
        ("%d channels not supported", n_channels));
    return GST_FLOW_ERROR;
  }
no_buffer:
  {
    GST_DEBUG ("Failed to create outbuffer - %s", gst_flow_get_name (ret));
    return ret;
  }
}
