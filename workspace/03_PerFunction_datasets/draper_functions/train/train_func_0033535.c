stroke(GfxState *state) {
  doPath(state->getPath());
  if (t3String) {


    writePS("Sf\n");
  } else {
    writePS("S\n");
  }
}
