default_prepare_output_buffer (GstBaseTransform * trans,
    GstBuffer * inbuf, GstBuffer ** outbuf)
{
  GstBaseTransformPrivate *priv;
  GstFlowReturn ret;
  GstBaseTransformClass *bclass;
  GstCaps *incaps, *outcaps;
  gsize insize, outsize;
  gboolean res;

  priv = trans->priv;
  bclass = GST_BASE_TRANSFORM_GET_CLASS (trans);


  if (priv->passthrough) {


    GST_DEBUG_OBJECT (trans, "passthrough: reusing input buffer");
    *outbuf = inbuf;
    goto done;
  }


  if (priv->pool) {
    if (!priv->pool_active) {
      GST_DEBUG_OBJECT (trans, "setting pool %p active", priv->pool);
      if (!gst_buffer_pool_set_active (priv->pool, TRUE))
        goto activate_failed;
      priv->pool_active = TRUE;
    }
    GST_DEBUG_OBJECT (trans, "using pool alloc");
    ret = gst_buffer_pool_acquire_buffer (priv->pool, outbuf, NULL);
    if (ret != GST_FLOW_OK)
      goto alloc_failed;

    goto copy_meta;
  }


  if ((bclass->transform_ip != NULL) && priv->always_in_place) {

    if (gst_buffer_is_writable (inbuf)) {
      GST_DEBUG_OBJECT (trans, "inplace reuse writable input buffer");
      *outbuf = inbuf;
    } else {
      GST_DEBUG_OBJECT (trans, "making writable buffer copy");

      *outbuf = gst_buffer_copy (inbuf);
    }
    goto done;
  }


  incaps = gst_pad_get_current_caps (trans->sinkpad);
  outcaps = gst_pad_get_current_caps (trans->srcpad);


  if (outcaps == NULL)
    goto no_outcaps;

  GST_DEBUG_OBJECT (trans, "getting output size for alloc");

  insize = gst_buffer_get_size (inbuf);
  res = gst_base_transform_transform_size (trans,
      GST_PAD_SINK, incaps, insize, outcaps, &outsize);

  gst_caps_unref (incaps);
  gst_caps_unref (outcaps);

  if (!res)
    goto unknown_size;

  GST_DEBUG_OBJECT (trans, "doing alloc of size %" G_GSIZE_FORMAT, outsize);
  *outbuf = gst_buffer_new_allocate (priv->allocator, outsize, &priv->params);
  if (!*outbuf) {
    ret = GST_FLOW_ERROR;
    goto alloc_failed;
  }

copy_meta:

  if (bclass->copy_metadata)
    if (!bclass->copy_metadata (trans, inbuf, *outbuf)) {

      GST_ELEMENT_WARNING (trans, STREAM, NOT_IMPLEMENTED,
          ("could not copy metadata"), (NULL));
    }

done:
  return GST_FLOW_OK;


activate_failed:
  {
    GST_ELEMENT_ERROR (trans, RESOURCE, SETTINGS,
        ("failed to activate bufferpool"), ("failed to activate bufferpool"));
    return GST_FLOW_ERROR;
  }
unknown_size:
  {
    GST_ERROR_OBJECT (trans, "unknown output size");
    return GST_FLOW_ERROR;
  }
alloc_failed:
  {
    GST_DEBUG_OBJECT (trans, "could not allocate buffer from pool");
    return ret;
  }
no_outcaps:
  {
    GST_DEBUG_OBJECT (trans, "no output caps, source pad has been deactivated");
    gst_caps_unref (incaps);
    return GST_FLOW_FLUSHING;
  }
}
