gst_decode_pad_handle_eos (GstDecodePad * pad)
{
  gboolean last_group = TRUE;
  gboolean switched = FALSE;
  gboolean drained = FALSE;
  GstDecodeChain *chain = pad->chain;
  GstDecodeBin *dbin = chain->dbin;

  GST_LOG_OBJECT (dbin, "pad %p", pad);
  drain_and_switch_chains (dbin->decode_chain, pad, &last_group, &drained,
      &switched);

  if (switched) {

    EXPOSE_LOCK (dbin);
    if (gst_decode_chain_is_complete (dbin->decode_chain))
      gst_decode_bin_expose (dbin);
    EXPOSE_UNLOCK (dbin);
  }

  return last_group;
}
