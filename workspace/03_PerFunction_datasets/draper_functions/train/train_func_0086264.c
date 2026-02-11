lto_new_out_decl_state (void)
{
  struct lto_out_decl_state *state = XCNEW (struct lto_out_decl_state);
  int i;
  htab_hash hash_fn;
  htab_eq eq_fn;

  for (i = 0; i < LTO_N_DECL_STREAMS; i++)
    {
      if (i == LTO_DECL_STREAM_TYPE)
	{
	  hash_fn = lto_hash_type_slot_node;
	  eq_fn = lto_eq_type_slot_node;
	}
      else
	{
	  hash_fn = lto_hash_decl_slot_node;
	  eq_fn = lto_eq_decl_slot_node;
	}
      lto_init_tree_ref_encoder (&state->streams[i], hash_fn, eq_fn);
    }

  return state;
}
