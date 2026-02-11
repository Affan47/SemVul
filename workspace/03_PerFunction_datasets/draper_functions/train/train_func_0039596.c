gst_pad_add_probe (GstPad * pad, GstPadProbeType mask,
    GstPadProbeCallback callback, gpointer user_data,
    GDestroyNotify destroy_data)
{
  GHook *hook;
  gulong res;

  g_return_val_if_fail (GST_IS_PAD (pad), 0);
  g_return_val_if_fail (mask != 0, 0);

  GST_OBJECT_LOCK (pad);


  hook = g_hook_alloc (&pad->probes);

  GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad, "adding probe for mask 0x%08x",
      mask);


  if ((mask & GST_PAD_PROBE_TYPE_ALL_BOTH) == 0)
    mask |= GST_PAD_PROBE_TYPE_ALL_BOTH;
  if ((mask & GST_PAD_PROBE_TYPE_SCHEDULING) == 0)
    mask |= GST_PAD_PROBE_TYPE_SCHEDULING;


  hook->flags |= (mask << G_HOOK_FLAG_USER_SHIFT);
  hook->func = callback;
  hook->data = user_data;
  hook->destroy = destroy_data;
  PROBE_COOKIE (hook) = (pad->priv->probe_cookie - 1);


  g_hook_prepend (&pad->probes, hook);
  pad->num_probes++;

  pad->priv->probe_list_cookie++;


  res = hook->hook_id;

  GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad, "got probe id %lu", res);

  if (mask & GST_PAD_PROBE_TYPE_BLOCKING) {

    pad->num_blocked++;
    GST_OBJECT_FLAG_SET (pad, GST_PAD_FLAG_BLOCKED);
    GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad, "added blocking probe, "
        "now %d blocking probes", pad->num_blocked);


    GST_PAD_BLOCK_BROADCAST (pad);
  }


  if ((mask & GST_PAD_PROBE_TYPE_IDLE) && (callback != NULL)) {
    if (pad->priv->using > 0) {


      GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad,
          "pad is in use, delay idle callback");
      GST_OBJECT_UNLOCK (pad);
    } else {
      GstPadProbeInfo info = { GST_PAD_PROBE_TYPE_IDLE, res, };
      GstPadProbeReturn ret;


      gst_object_ref (pad);


      GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad,
          "pad is idle, trigger idle callback");
      GST_OBJECT_UNLOCK (pad);

      ret = callback (pad, &info, user_data);

      GST_OBJECT_LOCK (pad);
      switch (ret) {
        case GST_PAD_PROBE_REMOVE:

          GST_DEBUG_OBJECT (pad, "asked to remove hook");
          cleanup_hook (pad, hook);
          res = 0;
          break;
        case GST_PAD_PROBE_DROP:
          GST_DEBUG_OBJECT (pad, "asked to drop item");
          break;
        case GST_PAD_PROBE_PASS:
          GST_DEBUG_OBJECT (pad, "asked to pass item");
          break;
        case GST_PAD_PROBE_OK:
          GST_DEBUG_OBJECT (pad, "probe returned OK");
          break;
        default:
          GST_DEBUG_OBJECT (pad, "probe returned %d", ret);
          break;
      }
      GST_OBJECT_UNLOCK (pad);

      gst_object_unref (pad);
    }
  } else {
    GST_OBJECT_UNLOCK (pad);
  }
  return res;
}
