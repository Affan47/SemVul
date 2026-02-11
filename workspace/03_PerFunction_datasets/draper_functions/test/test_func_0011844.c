find_stream_for_node (GstDiscoverer * dc, const GstStructure * topology)
{
  GstPad *pad;
  GstPad *target_pad = NULL;
  GstStructure *st = NULL;
  PrivateStream *ps;
  guint i;
  GList *tmp;

  if (!dc->priv->streams) {
    return NULL;
  }

  if (!gst_structure_id_has_field (topology, _TOPOLOGY_PAD_QUARK)) {
    GST_DEBUG ("Could not find pad for node %" GST_PTR_FORMAT, topology);
    return NULL;
  }

  gst_structure_id_get (topology, _TOPOLOGY_PAD_QUARK,
      GST_TYPE_PAD, &pad, NULL);

  for (i = 0, tmp = dc->priv->streams; tmp; tmp = tmp->next, i++) {
    ps = (PrivateStream *) tmp->data;

    target_pad = gst_ghost_pad_get_target (GST_GHOST_PAD (ps->pad));
    gst_object_unref (target_pad);

    if (target_pad == pad)
      break;
  }

  if (tmp)
    st = collect_stream_information (dc, ps, i);

  gst_object_unref (pad);

  return st;
}
