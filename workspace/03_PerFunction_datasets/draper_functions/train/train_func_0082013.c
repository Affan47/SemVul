generate_epsilon_closure(Block *b)
{
  int i, j, N;

  N = b->nstates;
  eclo = new_array(unsigned long*, N);
  for (i=0; i<N; i++) {
    eclo[i] = new_array(unsigned long, round_up(N));
    for (j=0; j<round_up(N); j++) {
      eclo[i][j] = 0;
    }
  }


  for (i=0; i<N; i++) {
    State *s = b->states[i];
    Translist *tl;
    int from_state = s->index;
    set_bit(eclo[from_state], from_state);

    for (tl=s->transitions; tl; tl=tl->next) {
      if (tl->token < 0) {
        int to_state = tl->ds_ref->index;
        set_bit(eclo[from_state], to_state);
        push_pair(from_state, to_state);
      }
    }
  }


  while (pop_pair(&i, &j)) {
    int k;
    for (k=0; k<N; k++) {
      if (is_set(eclo[j], k) && !is_set(eclo[i], k)) {
        set_bit(eclo[i], k);
        push_pair(i,k);
      }
    }
  }
}
