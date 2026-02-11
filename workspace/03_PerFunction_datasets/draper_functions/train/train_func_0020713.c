ParseIdentifier(State *state) {
  if (state->number == -1 ||
      RemainingLength(state) < state->number) {
    return false;
  }
  if (IdentifierIsAnonymousNamespace(state)) {
    MaybeAppend(state, "(anonymous namespace)");
  } else {
    MaybeAppendWithLength(state, state->mangled_cur, state->number);
  }
  state->mangled_cur += state->number;
  state->number = -1;
  return true;
}
