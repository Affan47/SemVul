gst_rtp_buffer_ext_timestamp (guint64 * exttimestamp, guint32 timestamp)
{
  guint64 result, diff, ext;

  g_return_val_if_fail (exttimestamp != NULL, -1);

  ext = *exttimestamp;

  if (ext == -1) {
    result = timestamp;
  } else {

    result = timestamp + (ext & ~(G_GUINT64_CONSTANT (0xffffffff)));


    if (result < ext)
      diff = ext - result;
    else
      diff = result - ext;

    if (diff > G_MAXINT32) {


      result += (G_GUINT64_CONSTANT (1) << 32);
    }
  }
  *exttimestamp = result;

  return result;
}
