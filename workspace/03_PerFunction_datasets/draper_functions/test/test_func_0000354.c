gst_collect_pads_set_clip_function (GstCollectPads * pads,
    GstCollectPadsClipFunction clipfunc, gpointer user_data)
{
  GstCollectPadsPrivate *priv;

  g_return_if_fail (pads != NULL);
  g_return_if_fail (GST_IS_COLLECT_PADS (pads));

  priv = pads->abidata.ABI.priv;

  priv->clipfunc = clipfunc;
  priv->clipfunc_user_data = user_data;
}
