read_header (EvdWebsocketData *data)
{
  guint16 header = 0;

  if (data->buf_len - data->offset < 2)
    return FALSE;

  header = ( (guint8) data->buf->str[data->offset] << 8) +
    (guint8) data->buf->str[data->offset + 1];

  data->offset += 2;


  data->fin = (guint16) (header & HEADER_MASK_FIN);


  data->opcode = (guint8) ((header & HEADER_MASK_OPCODE) >> 8);


  data->masked = (guint16) (header & HEADER_MASK_MASKED);


  data->payload_len = header & HEADER_MASK_PAYLOAD_LEN;


  if (data->payload_len > 125)
    data->reading_state = EVD_WEBSOCKET_READING_STATE_PAYLOAD_LEN;
  else if (data->masked)
    data->reading_state = EVD_WEBSOCKET_READING_STATE_MASKING_KEY;
  else
    data->reading_state = EVD_WEBSOCKET_READING_STATE_PAYLOAD;

  return TRUE;
}
