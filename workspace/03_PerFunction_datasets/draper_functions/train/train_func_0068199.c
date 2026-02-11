restoreStateStack(GfxState *oldState) {
  while (state->hasSaves()) {
    restoreState();
  }
  delete state;
  state = oldState;
  out->restoreState(state);
}
