gst_dp_header_payload_length (const guint8 * header)
{
  g_return_val_if_fail (header != NULL, 0);

  return GST_DP_HEADER_PAYLOAD_LENGTH (header);
}
