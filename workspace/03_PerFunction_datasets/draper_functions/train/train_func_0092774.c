gst_deinterleave_sink_getcaps (GstPad * pad, GstObject * parent,
    GstCaps * filter)
{
  GstDeinterleave *self = GST_DEINTERLEAVE (parent);
  GstCaps *ret;
  GList *l;

  GST_OBJECT_LOCK (self);


  ret = gst_caps_new_any ();
  for (l = GST_ELEMENT (self)->pads; l != NULL; l = l->next) {
    GstPad *ourpad = GST_PAD (l->data);
    GstCaps *peercaps = NULL, *ourcaps;

    ourcaps = gst_caps_copy (gst_pad_get_pad_template_caps (ourpad));

    if (pad == ourpad) {
      if (GST_PAD_DIRECTION (pad) == GST_PAD_SINK)
        __set_channels (ourcaps, GST_AUDIO_INFO_CHANNELS (&self->audio_info));
      else
        __set_channels (ourcaps, 1);
    } else {
      __remove_channels (ourcaps);


      peercaps = gst_pad_peer_query_caps (ourpad, NULL);
      peercaps = gst_caps_make_writable (peercaps);
    }


    if (peercaps) {
      GstCaps *intersection;
      GstCaps *oldret = ret;

      __remove_channels (peercaps);

      intersection = gst_caps_intersect (peercaps, ourcaps);

      ret = gst_caps_intersect (ret, intersection);
      gst_caps_unref (intersection);
      gst_caps_unref (peercaps);
      gst_caps_unref (oldret);
    } else {
      GstCaps *oldret = ret;

      ret = gst_caps_intersect (ret, ourcaps);
      gst_caps_unref (oldret);
    }
    gst_caps_unref (ourcaps);
  }
  GST_OBJECT_UNLOCK (self);

  GST_DEBUG_OBJECT (pad, "Intersected caps to %" GST_PTR_FORMAT, ret);

  return ret;
}
