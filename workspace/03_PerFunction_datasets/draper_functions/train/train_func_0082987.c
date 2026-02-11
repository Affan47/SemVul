stun_agent_init_request (StunAgent *agent, StunMessage *msg,
    uint8_t *buffer, size_t buffer_len, StunMethod m)
{
  bool ret;
  StunTransactionId id;

  msg->buffer = buffer;
  msg->buffer_len = buffer_len;
  msg->agent = agent;
  msg->key = NULL;
  msg->key_len = 0;
  msg->long_term_valid = FALSE;

  stun_make_transid (id);

  ret = stun_message_init (msg, STUN_REQUEST, m, id);

  if (ret) {
    if (agent->compatibility == STUN_COMPATIBILITY_RFC5389 ||
        agent->compatibility == STUN_COMPATIBILITY_WLM2009) {
      uint32_t cookie = htonl (STUN_MAGIC_COOKIE);
      memcpy (msg->buffer + STUN_MESSAGE_TRANS_ID_POS, &cookie, sizeof (cookie));
    }
    if ((agent->compatibility == STUN_COMPATIBILITY_RFC5389 ||
            agent->compatibility == STUN_COMPATIBILITY_WLM2009) &&
        (agent->software_attribute != NULL ||
            agent->usage_flags & STUN_AGENT_USAGE_ADD_SOFTWARE)) {
      stun_message_append_software (msg, agent->software_attribute);
    }
  }

  return ret;
}
