fs_rawudp_transmitter_put_udpport (FsRawUdpTransmitter *trans,
  UdpPort *udpport)
{
  GST_LOG ("Put port refcount %d->%d", udpport->refcount, udpport->refcount-1);

  g_mutex_lock (&trans->priv->mutex);

  if (udpport->refcount > 1)
  {
    udpport->refcount--;
    g_mutex_unlock (&trans->priv->mutex);
    return;
  }

  trans->priv->udpports[udpport->component_id] =
    g_list_remove (trans->priv->udpports[udpport->component_id], udpport);

  g_mutex_unlock (&trans->priv->mutex);

  if (udpport->udpsrc)
  {
    GstStateChangeReturn ret;
    gst_element_set_locked_state (udpport->udpsrc, TRUE);
    ret = gst_element_set_state (udpport->udpsrc, GST_STATE_NULL);
    if (ret != GST_STATE_CHANGE_SUCCESS)
      GST_ERROR ("Error changing state of udpsrc: %s",
          gst_element_state_change_return_get_name (ret));
    if (!gst_bin_remove (GST_BIN (trans->priv->gst_src), udpport->udpsrc))
      GST_ERROR ("Could not remove udpsrc element from transmitter source");
  }

  if (udpport->udpsrc_requested_pad)
  {
    gst_element_release_request_pad (udpport->funnel,
        udpport->udpsrc_requested_pad);
    gst_object_unref (udpport->udpsrc_requested_pad);
  }

  if (udpport->udpsink_requested_pad)
  {
    gst_element_release_request_pad (udpport->tee,
        udpport->udpsink_requested_pad);
    gst_object_unref (udpport->udpsink_requested_pad);
  }

  if (udpport->udpsink)
  {
    GstStateChangeReturn ret;
    gst_element_set_locked_state (udpport->udpsink, TRUE);
    ret = gst_element_set_state (udpport->udpsink, GST_STATE_NULL);
    if (ret != GST_STATE_CHANGE_SUCCESS)
      GST_ERROR ("Error changing state of udpsink: %s",
          gst_element_state_change_return_get_name (ret));
    if (!gst_bin_remove (GST_BIN (trans->priv->gst_sink), udpport->udpsink))
      GST_ERROR ("Could not remove udpsink element from transmitter source");
  }

  if (udpport->recvonly_requested_pad)
  {
    gst_element_release_request_pad (udpport->tee,
        udpport->recvonly_requested_pad);
    gst_object_unref (udpport->recvonly_requested_pad);
  }

  if (udpport->recvonly_udpsink)
  {
    GstStateChangeReturn ret;
    gst_element_set_locked_state (udpport->recvonly_udpsink, TRUE);
    ret = gst_element_set_state (udpport->recvonly_udpsink, GST_STATE_NULL);
    if (ret != GST_STATE_CHANGE_SUCCESS)
      GST_ERROR ("Error changing state of udpsink: %s",
          gst_element_state_change_return_get_name (ret));
    if (!gst_bin_remove (GST_BIN (trans->priv->gst_sink),
            udpport->recvonly_udpsink))
      GST_ERROR ("Could not remove udpsink element from transmitter source");
  }


  if (udpport->socket)
    g_socket_close (udpport->socket, NULL);
  g_clear_object (&udpport->socket);

  if (udpport->known_addresses)
  {
    guint i;
    for (i = 0; i < udpport->known_addresses->len; i++)
      g_object_unref (g_array_index (udpport->known_addresses,
              struct KnownAddress, i).addr);
    g_array_free (udpport->known_addresses, TRUE);
  }

  g_free (udpport->requested_ip);
  g_mutex_clear (&udpport->mutex);
  g_slice_free (UdpPort, udpport);
}
