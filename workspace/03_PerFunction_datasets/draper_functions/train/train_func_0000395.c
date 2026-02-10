read_line (GstRTSPConnection * conn, guint8 * buffer, guint * idx, guint size)
{
  while (TRUE) {
    guint8 c;
    gint r;

    if (conn->read_ahead == READ_AHEAD_EOH) {


      conn->read_ahead = 0;
      break;
    } else if (conn->read_ahead == READ_AHEAD_CRLF) {

      c = '\n';
    } else if (conn->read_ahead == READ_AHEAD_CRLFCR) {

      c = '\r';
    } else if (conn->read_ahead != 0) {

      c = (guint8) conn->read_ahead;
      conn->read_ahead = 0;
    } else {

      r = fill_bytes (conn, &c, 1);
      if (G_UNLIKELY (r == 0)) {
        return GST_RTSP_EEOF;
      } else if (G_UNLIKELY (r < 0)) {
        if (ERRNO_IS_EAGAIN)
          return GST_RTSP_EINTR;
        if (!ERRNO_IS_EINTR)
          return GST_RTSP_ESYS;
        continue;
      }
    }


    if (c == '\r' || c == '\n') {
      guint8 read_ahead;

    retry:

      r = fill_bytes (conn, &read_ahead, 1);
      if (G_UNLIKELY (r == 0)) {
        return GST_RTSP_EEOF;
      } else if (G_UNLIKELY (r < 0)) {
        if (ERRNO_IS_EAGAIN) {

          if (conn->read_ahead == 0)
            conn->read_ahead = c;
          return GST_RTSP_EINTR;
        }
        if (!ERRNO_IS_EINTR)
          return GST_RTSP_ESYS;
        goto retry;
      }

      if (read_ahead == ' ' || read_ahead == '\t') {
        if (conn->read_ahead == READ_AHEAD_CRLFCR) {


          conn->read_ahead = read_ahead;
          break;
        } else {

          c = ' ';
          conn->read_ahead = read_ahead;
        }
      } else if (conn->read_ahead == READ_AHEAD_CRLFCR) {
        if (read_ahead == '\r' || read_ahead == '\n') {

          conn->read_ahead = READ_AHEAD_EOH;
          break;
        } else {


          conn->read_ahead = read_ahead;
          break;
        }
      } else if (conn->read_ahead == READ_AHEAD_CRLF) {
        if (read_ahead == '\r') {

          conn->read_ahead = READ_AHEAD_CRLFCR;
          goto retry;
        } else if (read_ahead == '\n') {

          conn->read_ahead = READ_AHEAD_EOH;
          break;
        } else {

          conn->read_ahead = read_ahead;
          break;
        }
      } else if (c == read_ahead) {

        conn->read_ahead = READ_AHEAD_EOH;
        break;
      } else if (c == '\r' && read_ahead == '\n') {

        conn->read_ahead = READ_AHEAD_CRLF;
        goto retry;
      } else {

        conn->read_ahead = read_ahead;
        break;
      }
    }

    if (G_LIKELY (*idx < size - 1))
      buffer[(*idx)++] = c;
  }
  buffer[*idx] = '\0';

  return GST_RTSP_OK;
}
