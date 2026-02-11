old_stun_init_success_response_str(u16bits method, u08bits* buf, size_t *len, stun_tid* id, u32bits cookie) {
  old_stun_init_command_str(stun_make_success_response(method), buf, len, cookie);
  if(id) {
    stun_tid_message_cpy(buf, id);
  }
}
