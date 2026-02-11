ssh_free(ssh_session session) {
  int i;
  struct ssh_iterator *it;

  if (session == NULL) {
    return;
  }


  for (it = ssh_list_get_iterator(session->channels);
       it != NULL;
       it = ssh_list_get_iterator(session->channels)) {
      ssh_channel_do_free(ssh_iterator_value(ssh_channel,it));
      ssh_list_remove(session->channels, it);
  }
  ssh_list_free(session->channels);
  session->channels = NULL;

#ifdef WITH_PCAP
  if (session->pcap_ctx) {
      ssh_pcap_context_free(session->pcap_ctx);
      session->pcap_ctx = NULL;
  }
#endif

  ssh_socket_free(session->socket);
  session->socket = NULL;

  if (session->default_poll_ctx) {
      ssh_poll_ctx_free(session->default_poll_ctx);
  }

  ssh_buffer_free(session->in_buffer);
  ssh_buffer_free(session->out_buffer);
  session->in_buffer = session->out_buffer = NULL;

  if (session->in_hashbuf != NULL) {
      ssh_buffer_free(session->in_hashbuf);
  }
  if (session->out_hashbuf != NULL) {
      ssh_buffer_free(session->out_hashbuf);
  }

  crypto_free(session->current_crypto);
  crypto_free(session->next_crypto);

#ifndef _WIN32
  agent_free(session->agent);
#endif

  ssh_key_free(session->srv.dsa_key);
  ssh_key_free(session->srv.rsa_key);

  if (session->ssh_message_list) {
      ssh_message msg;

      for (msg = ssh_list_pop_head(ssh_message, session->ssh_message_list);
           msg != NULL;
           msg = ssh_list_pop_head(ssh_message, session->ssh_message_list)) {
          ssh_message_free(msg);
      }
      ssh_list_free(session->ssh_message_list);
  }

  if (session->packet_callbacks) {
    ssh_list_free(session->packet_callbacks);
  }


  if (session->opts.identity) {
      char *id;

      for (id = ssh_list_pop_head(char *, session->opts.identity);
           id != NULL;
           id = ssh_list_pop_head(char *, session->opts.identity)) {
          SAFE_FREE(id);
      }
      ssh_list_free(session->opts.identity);
  }

  SAFE_FREE(session->serverbanner);
  SAFE_FREE(session->clientbanner);
  SAFE_FREE(session->banner);

  SAFE_FREE(session->opts.bindaddr);
  SAFE_FREE(session->opts.username);
  SAFE_FREE(session->opts.host);
  SAFE_FREE(session->opts.sshdir);
  SAFE_FREE(session->opts.knownhosts);
  SAFE_FREE(session->opts.ProxyCommand);

  for (i = 0; i < 10; i++) {
      if (session->opts.wanted_methods[i]) {
          SAFE_FREE(session->opts.wanted_methods[i]);
      }
  }


  BURN_BUFFER(session, sizeof(struct ssh_session_struct));
  SAFE_FREE(session);
}
