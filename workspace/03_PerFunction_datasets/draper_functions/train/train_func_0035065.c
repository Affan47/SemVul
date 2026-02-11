rnd_int(Rnd *state)  {
  uint  result;
  int  destIndent;

  assert(MAGIC(state));
  destIndent = state->indent + RND_INDENT;
  if (destIndent >= RND_DATASIZE)
    destIndent -= RND_DATASIZE;
  result = (state->data[destIndent] += state->data[state->indent]);
  if (++state->indent >= RND_DATASIZE)
    state->indent = 0;
  return((int)(result >> 1));
}
