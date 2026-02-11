pad_added_cb (GESTrack * track, GstPad * pad, TrackPrivate * tr_priv)
{
  gchar *padname;
  gboolean no_more;
  GList *tmp;

  GST_DEBUG ("track:%p, pad:%s:%s", track, GST_DEBUG_PAD_NAME (pad));

  if (G_UNLIKELY (tr_priv->pad)) {
    GST_WARNING ("We are already controlling a pad for this track");
    return;
  }


  LOCK_DYN (tr_priv->timeline);
  GST_OBJECT_LOCK (track);
  tr_priv->pad = pad;

  no_more = TRUE;
  for (tmp = tr_priv->timeline->priv->priv_tracks; tmp; tmp = g_list_next (tmp)) {
    TrackPrivate *tr_priv = (TrackPrivate *) tmp->data;

    if (!tr_priv->pad) {
      GST_LOG ("Found track without pad %p", tr_priv->track);
      no_more = FALSE;
    }
  }
  GST_OBJECT_UNLOCK (track);


  GST_DEBUG ("Ghosting pad and adding it to ourself");
  padname = g_strdup_printf ("track_%p_src", track);
  tr_priv->ghostpad = gst_ghost_pad_new (padname, pad);
  g_free (padname);
  gst_pad_set_active (tr_priv->ghostpad, TRUE);
  gst_element_add_pad (GST_ELEMENT (tr_priv->timeline), tr_priv->ghostpad);

  if (no_more) {
    GST_DEBUG ("Signaling no-more-pads");
    gst_element_no_more_pads (GST_ELEMENT (tr_priv->timeline));
  }

  tr_priv->probe_id = gst_pad_add_probe (pad,
      GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM,
      (GstPadProbeCallback) _pad_probe_cb, tr_priv->timeline, NULL);

  UNLOCK_DYN (tr_priv->timeline);
}
