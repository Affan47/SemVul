gst_base_parse_drain (GstBaseParse * parse)
{
  guint avail;

  GST_DEBUG_OBJECT (parse, "draining");
  parse->priv->drain = TRUE;

  for (;;) {
    avail = gst_adapter_available (parse->priv->adapter);
    if (!avail)
      break;

    if (gst_base_parse_chain (parse->sinkpad, GST_OBJECT_CAST (parse),
            NULL) != GST_FLOW_OK) {
      break;
    }


    if (avail == gst_adapter_available (parse->priv->adapter)) {
      GST_DEBUG_OBJECT (parse, "no change during draining; flushing");
      gst_adapter_clear (parse->priv->adapter);
    }
  }

  parse->priv->drain = FALSE;
}
