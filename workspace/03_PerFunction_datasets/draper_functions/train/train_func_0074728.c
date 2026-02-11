gst_base_transform_acceptcaps_default (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps)
{
#if 0
  GstPad *otherpad;
  GstCaps *othercaps = NULL;
#endif
  gboolean ret = TRUE;

#if 0
  otherpad = (pad == trans->srcpad) ? trans->sinkpad : trans->srcpad;


  if (!gst_caps_is_fixed (caps))
#endif
  {
    GstCaps *allowed;

    GST_DEBUG_OBJECT (trans, "accept caps %" GST_PTR_FORMAT, caps);


    if (direction == GST_PAD_SRC)
      allowed = gst_pad_query_caps (trans->srcpad, caps);
    else
      allowed = gst_pad_query_caps (trans->sinkpad, caps);

    if (!allowed) {
      GST_DEBUG_OBJECT (trans, "gst_pad_query_caps() failed");
      goto no_transform_possible;
    }

    GST_DEBUG_OBJECT (trans, "allowed caps %" GST_PTR_FORMAT, allowed);


    ret = gst_caps_is_subset (caps, allowed);
    gst_caps_unref (allowed);

    if (!ret)
      goto no_transform_possible;
  }
#if 0
  else {
    GST_DEBUG_OBJECT (pad, "accept caps %" GST_PTR_FORMAT, caps);


    othercaps = gst_base_transform_find_transform (trans, pad, caps, FALSE);
    if (!othercaps || gst_caps_is_empty (othercaps))
      goto no_transform_possible;

    GST_DEBUG_OBJECT (pad, "we can transform to %" GST_PTR_FORMAT, othercaps);
  }
#endif

done:
#if 0

  if (othercaps)
    gst_caps_unref (othercaps);
#endif

  return ret;


no_transform_possible:
  {
    GST_DEBUG_OBJECT (trans,
        "transform could not transform %" GST_PTR_FORMAT
        " in anything we support", caps);
    ret = FALSE;
    goto done;
  }
}
