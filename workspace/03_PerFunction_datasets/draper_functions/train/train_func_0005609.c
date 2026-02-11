gst_base_transform_can_transform (GstBaseTransform * trans, GstPad * pad,
    GstCaps * in, GstCaps * out)
{
  GstCaps *othercaps;


  othercaps =
      gst_base_transform_transform_caps (trans, GST_PAD_DIRECTION (pad), in);


  if (!othercaps || gst_caps_is_empty (othercaps))
    goto no_transform;


  if (!gst_caps_can_intersect (out, othercaps))
    goto no_subset;

  if (othercaps)
    gst_caps_unref (othercaps);

  GST_DEBUG_OBJECT (trans, "from %" GST_PTR_FORMAT, in);
  GST_DEBUG_OBJECT (trans, "to   %" GST_PTR_FORMAT, out);

  return TRUE;


no_transform:
  {
    GST_DEBUG_OBJECT (trans,
        "transform returned useless %" GST_PTR_FORMAT, othercaps);
    if (othercaps)
      gst_caps_unref (othercaps);
    return FALSE;
  }
no_subset:
  {
    GST_DEBUG_OBJECT (trans, "no subset");
    if (othercaps)
      gst_caps_unref (othercaps);
    return FALSE;
  }
}
