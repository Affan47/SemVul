process_data (EvdWebsocketData *data)
{
  while (data->offset < data->buf_len &&
         data->state != EVD_WEBSOCKET_STATE_CLOSED)
    {
      if (data->reading_state == EVD_WEBSOCKET_READING_STATE_IDLE)
        if (! read_header (data))
          return TRUE;

      switch (data->reading_state)
        {
        case EVD_WEBSOCKET_READING_STATE_PAYLOAD_LEN:
          if (! read_payload_len (data))
            return TRUE;
          break;

        case EVD_WEBSOCKET_READING_STATE_MASKING_KEY:
          if (! read_masking_key (data))
            return TRUE;
          break;

        case EVD_WEBSOCKET_READING_STATE_PAYLOAD:
          if (! read_payload (data))
            return TRUE;
          break;

        default:
          {

          }
        }
    }

  return data->state != EVD_WEBSOCKET_STATE_CLOSED;
}
