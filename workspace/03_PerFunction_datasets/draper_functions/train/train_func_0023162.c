gst_asm_scan_new (const gchar * buffer)
{
  GstASMScan *scan;

  scan = g_new0 (GstASMScan, 1);
  scan->buffer = buffer;
  NEXT_CHAR (scan);

  return scan;
}
