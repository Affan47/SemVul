msg_marshal(struct evbuffer *evbuf, const struct msg *tmp){
  evtag_marshal_string(evbuf, MSG_FROM_NAME, tmp->from_name_data);
  evtag_marshal_string(evbuf, MSG_TO_NAME, tmp->to_name_data);
  if (tmp->attack_set) {
    evtag_marshal_kill(evbuf, MSG_ATTACK, tmp->attack_data);
  }
  if (tmp->run_set) {
    {
      int i;
      for (i = 0; i < tmp->run_length; ++i) {
    evtag_marshal_run(evbuf, MSG_RUN, tmp->run_data[i]);
      }
    }
  }
}
