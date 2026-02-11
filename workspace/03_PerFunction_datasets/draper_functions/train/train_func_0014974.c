skytraq_expect_msg(gbuint8 id, const gbuint8 *payload, int len)
{
  int i, rc;

  for (i = 0; i < MSG_RETRIES; i++) {
    rc = skytraq_rd_msg(payload, len);
    if (rc < 0) {
      return rc;
    }
    if (payload[0] == id) {
      return len;
    }
  }

  return res_PROTOCOL_ERR;
}
