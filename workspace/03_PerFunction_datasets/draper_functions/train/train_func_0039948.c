nxt_hid_send_str(nxt_t *nxt, int port, const char *str) {
  int i;

  nxt_hid_set_mode(nxt, port, NXT_HID_MODE_ASCII);
  nxt_wait_after_communication_command();

  for (i=0; str[i]; i++) {
    nxt_hid_set_key(nxt, port, str[i]);
    nxt_wait_after_communication_command();

    nxt_hid_transmit(nxt, port);
    nxt_wait_after_communication_command();
  }

  return 0;
}
