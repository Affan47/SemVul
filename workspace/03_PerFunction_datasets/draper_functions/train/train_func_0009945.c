probe_avi(bgav_input_context_t * input)
  {
  uint8_t data[12];
  if(bgav_input_get_data(input, data, 12) < 12)
    return 0;

  if ((data[0] == 'R') &&
      (data[1] == 'I') &&
      (data[2] == 'F') &&
      (data[3] == 'F') &&
      (data[8] == 'A') &&
      (data[9] == 'V') &&
      (data[10] == 'I') &&
      (data[11] == ' '))
    return 1;
  else if((data[0] == 'O') &&
          (data[1] == 'N') &&
          (data[2] == '2') &&
          (data[3] == ' ') &&
          (data[8] == 'O') &&
          (data[9] == 'N') &&
          (data[10] == '2') &&
          (data[11] == 'f'))
    return 1;
  else
    return 0;

  }
