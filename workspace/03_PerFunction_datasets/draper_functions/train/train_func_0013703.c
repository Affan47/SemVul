fetch_stamp(int id, SAMPLE_BUFFER* x) {
  if (stamp_map_rep.find(id) == stamp_map_rep.end()) {
    x->make_silent();

  }
  else {
    AUDIO_STAMP* p = stamp_map_rep[id];
    p->fetch_stamp(x);

  }
}
