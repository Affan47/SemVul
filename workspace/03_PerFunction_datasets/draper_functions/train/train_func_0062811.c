dvdread_getbits(getbits_state_t *state, uint32_t number_of_bits) {
  uint32_t result=0;
  uint8_t byte=0;
  if (number_of_bits > 32) {
    printf("Number of bits > 32 in getbits\n");
    abort();
  }

  if ((state->bit_position) > 0) {
    if (number_of_bits > (8-state->bit_position)) {
      byte = state->byte;
      byte = byte >> (state->bit_position);
      result = byte;
      number_of_bits -= (8-state->bit_position);
      state->bit_position = 0;
      state->byte_position++;
      state->byte = state->start[state->byte_position];
    } else {
      byte=state->byte;
      state->byte = state->byte << number_of_bits;
      byte = byte >> (8 - number_of_bits);
      result = byte;
      state->bit_position += number_of_bits;
      if (state->bit_position == 8) {
        state->bit_position = 0;
        state->byte_position++;
        state->byte = state->start[state->byte_position];
      }
      number_of_bits = 0;
    }
  }
  if ((state->bit_position) == 0) {
    while (number_of_bits > 7) {
      result = (result << 8) + state->byte;
      state->byte_position++;
      state->byte = state->start[state->byte_position];
      number_of_bits -= 8;
    }
    if (number_of_bits > 0) {
      byte = state->byte;
      state->byte = state->byte << number_of_bits;
      state->bit_position += number_of_bits;
      byte = byte >> (8 - number_of_bits);
      result = (result << number_of_bits) + byte;
      number_of_bits = 0;
    }
  }

  return result;
}
