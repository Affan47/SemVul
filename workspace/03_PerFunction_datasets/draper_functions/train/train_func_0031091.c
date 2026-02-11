gst_collect_pads_handle_position_update (GstCollectPads * pads,
    GstCollectData * data, GstClockTime new_pos)
{
  gint cmp_res;


  if (!pads->priv->earliest_data || pads->priv->earliest_data == data) {
    gst_collect_pads_recalculate_full (pads);
    goto exit;
  }


  cmp_res =
      pads->priv->compare_func (pads, data, new_pos,
      pads->priv->earliest_data, pads->priv->earliest_time,
      pads->priv->compare_user_data);

  if (cmp_res > 0)

    gst_collect_pads_set_waiting (pads, data, FALSE);

exit:
  return;

}
