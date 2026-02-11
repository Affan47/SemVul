remove_event (t_algo_state& state, t_event_it it) {
  p_event ev = *it;
  t_event_it next_it = inc(it);


  state.events.erase(it);
  delete ev;
  return next_it;
}
