stun_tid_message_cpy(u08bits* buf, const stun_tid* id) {
  if(buf && id) {
    stun_tid_string_cpy(buf+8, id);
  }
}
