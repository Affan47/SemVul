tex2state(GemState*state, TexCoord*coords, int size) {
  state->set(GemState::_GL_TEX_COORDS, coords);
  state->set(GemState::_GL_TEX_NUMCOORDS, size);
}
