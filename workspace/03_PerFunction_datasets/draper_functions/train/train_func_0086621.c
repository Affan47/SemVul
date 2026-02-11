beginTextObject(GfxState *state) {
  if (state->getFillColorSpace()->getMode() == csPattern) {
    haveCSPattern = gTrue;
    saveState(state);
    savedRender = state->getRender();
    state->setRender(7);
  }
}
