lto_output_decl_state_streams (struct output_block *ob,
			       struct lto_out_decl_state *state)
{
  int i;

  for (i = 0;  i < LTO_N_DECL_STREAMS; i++)
    write_global_stream (ob, &state->streams[i]);
}
