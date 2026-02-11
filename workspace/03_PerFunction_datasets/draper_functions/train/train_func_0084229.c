remove_event (t_algo_state& state, t_event_it start, t_event_it end) {
  t_event_it it = start;
  while (it != end) {
    it = remove_event(state, it);
  }
  return it;
}
