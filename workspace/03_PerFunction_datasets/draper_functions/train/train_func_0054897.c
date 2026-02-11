stroke(GfxState *state) {
  SplashPath *path;

  if (state->getStrokeColorSpace()->isNonMarking()) {
    return;
  }
  path = convertPath(state, state->getPath());
  splash->stroke(path);
  delete path;
}
