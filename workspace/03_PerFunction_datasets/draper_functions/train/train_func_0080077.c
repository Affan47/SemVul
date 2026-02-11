lto_delete_in_decl_state (struct lto_in_decl_state *state)
{
  int i;

  for (i = 0; i < LTO_N_DECL_STREAMS; i++)
    if (state->streams[i].trees)
      ggc_free (state->streams[i].trees);
  ggc_free (state);
}
