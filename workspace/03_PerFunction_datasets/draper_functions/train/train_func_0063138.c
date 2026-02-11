stun_is_binding_response_str(const u08bits* buf, size_t len) {
  if(stun_is_command_message_str(buf,len) &&
     (stun_get_method_str(buf,len)==STUN_METHOD_BINDING)) {
    if(stun_is_response_str(buf,len)) {
      return 1;
    }
  }
  return 0;
}
