MaybeAppend(State *state, const char * const str) {
  if (state->append) {
    int length = StrLen(str);
    MaybeAppendWithLength(state, str, length);
  }
  return true;
}
