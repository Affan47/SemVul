append_data(bgav_packet_t * p, uint8_t * data, int len,
                        int header_len)
  {
  switch(header_len)
    {
    case 3:
      bgav_packet_alloc(p, p->data_size + 3 + len);
      memcpy(p->data + p->data_size, &nal_header[1], 3);
      p->data_size += 3;
      break;
    case 4:
      bgav_packet_alloc(p, p->data_size + 4 + len);
      memcpy(p->data + p->data_size, nal_header, 4);
      p->data_size += 4;
      break;
    }
  memcpy(p->data + p->data_size, data, len);
  p->data_size += len;
  }
