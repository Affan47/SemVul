guess_packet_size(bgav_input_context_t * input)
  {
  uint8_t probe_data[PROBE_SIZE];
  if(bgav_input_get_data(input, probe_data, PROBE_SIZE) < PROBE_SIZE)
    return 0;

  if(test_packet_size(probe_data, TS_FEC_PACKET_SIZE))
    return TS_FEC_PACKET_SIZE;
  if(test_packet_size(probe_data, TS_DVHS_PACKET_SIZE))
    return TS_DVHS_PACKET_SIZE;
  if(test_packet_size(probe_data, TS_PACKET_SIZE))
    return TS_PACKET_SIZE;

  return 0;
  }
