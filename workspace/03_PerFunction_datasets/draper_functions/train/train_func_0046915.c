bigint_to_int(bigint* p_bigint) {
  int index;
  int value;

  index = p_bigint->data_len - 1;

  value = 0;

  while (index >= 0) {
    value *= BIGINT_RADIX;
    value += p_bigint->p_data[index];
    index--;
  }

  if (p_bigint->sign == -1) {
    value = -value;
  }

  return value;
}
