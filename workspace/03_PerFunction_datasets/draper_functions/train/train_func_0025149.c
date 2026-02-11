echoThreadStateNix(echoThreadState *state) {

  if (state) {
    state->thread = airThreadNix(state->thread);
    nrrdNuke(state->njitt);
    nrrdNuke(state->nperm);
    state->permBuff = AIR_CAST(unsigned int *, airFree(state->permBuff));
    state->chanBuff = AIR_CAST(echoCol_t *, airFree(state->chanBuff));
    airFree(state);
  }
  return NULL;
}
