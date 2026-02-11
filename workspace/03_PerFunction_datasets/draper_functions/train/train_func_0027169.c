stun_is_indication(const stun_buffer* buf) {
  if(is_channel_msg(buf)) return 0;
  return IS_STUN_INDICATION(stun_get_msg_type(buf));
}
