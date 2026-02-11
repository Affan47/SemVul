gst_insert_bin_block_pad_unlock (GstInsertBin * self)
{
  struct ChangeData *data;
  GstPad *pad;
  GstPadProbeType probetype;

again:

  data = g_queue_peek_head (&self->priv->change_queue);
  if (!data) {
    GST_OBJECT_UNLOCK (self);
    return;
  }

  if (data->action == GST_INSERT_BIN_ACTION_ADD &&
      !validate_element (self, data->element))
    goto error;

  if (data->action == GST_INSERT_BIN_ACTION_ADD) {
    if (data->sibling) {
      if (data->direction == DIRECTION_BEFORE)
        pad = get_single_pad (data->sibling, GST_PAD_SINK);
      else
        pad = get_single_pad (data->sibling, GST_PAD_SRC);
    } else {
      if (data->direction == DIRECTION_BEFORE)
        pad = (GstPad *)
            gst_proxy_pad_get_internal (GST_PROXY_PAD (self->priv->srcpad));
      else
        pad = (GstPad *)
            gst_proxy_pad_get_internal (GST_PROXY_PAD (self->priv->sinkpad));
    }

    if (!pad) {
      GST_WARNING_OBJECT (self, "Can not obtain a sibling pad to block"
          " before adding");
      goto error;
    }

    if (!is_right_direction_for_block (pad)) {
      GstPad *peer = gst_pad_get_peer (pad);

      if (peer) {
        gst_object_unref (pad);
        pad = peer;
      }
    }
  } else {
    GstPad *element_pad;

    element_pad = get_single_pad (data->element, GST_PAD_SINK);
    if (!element_pad) {
      GST_WARNING_OBJECT (self, "Can not obtain the element's sink pad");
      goto error;
    }

    if (!is_right_direction_for_block (element_pad)) {
      pad = gst_pad_get_peer (element_pad);
    } else {
      gst_object_unref (element_pad);

      element_pad = get_single_pad (data->element, GST_PAD_SRC);
      if (!element_pad) {
        GST_WARNING_OBJECT (self, "Can not obtain the element's src pad");
        goto error;
      }

      pad = gst_pad_get_peer (element_pad);
    }
    gst_object_unref (element_pad);

    if (!pad) {
      GST_WARNING_OBJECT (self, "Can not obtain a sibling pad for removing");
      goto error;
    }
  }

  if (GST_PAD_IS_SRC (pad))
    probetype = GST_PAD_PROBE_TYPE_BLOCK_DOWNSTREAM;
  else
    probetype = GST_PAD_PROBE_TYPE_BLOCK_UPSTREAM;

  GST_OBJECT_UNLOCK (self);
  gst_pad_add_probe (pad, GST_PAD_PROBE_TYPE_IDLE | probetype, pad_blocked_cb,
      self, NULL);
  gst_object_unref (pad);
  return;

error:
  g_queue_pop_head (&self->priv->change_queue);
  gst_insert_bin_change_data_complete (self, data, FALSE);
  goto again;
}
