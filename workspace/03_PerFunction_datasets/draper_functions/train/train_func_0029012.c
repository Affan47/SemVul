clip(GfxState *state) {
  SplashPath *path;

  path = convertPath(state, state->getPath(), gTrue);
  splash->clipToPath(path, gFalse);
  delete path;
}
