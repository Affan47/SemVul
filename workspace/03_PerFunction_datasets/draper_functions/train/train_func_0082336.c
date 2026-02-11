stat_test_monobit(uint8_t *data) {
  uint8_t *data_end = data + STAT_TEST_DATA_LEN;
  uint16_t ones_count;

  ones_count = 0;
  while (data < data_end) {
    ones_count += octet_get_weight(*data);
    data++;
  }

  debug_print(mod_stat, "bit count: %d", ones_count);

  if ((ones_count < 9725) || (ones_count > 10275))
    return err_status_algo_fail;

  return err_status_ok;
}
