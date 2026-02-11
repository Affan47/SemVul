ipa_edge_duplication_hook (struct cgraph_edge *src, struct cgraph_edge *dst,
			   __attribute__((unused)) void *data)
{
  struct ipa_edge_args *old_args, *new_args;
  int arg_count;

  ipa_check_create_edge_args ();

  old_args = IPA_EDGE_REF (src);
  new_args = IPA_EDGE_REF (dst);

  arg_count = ipa_get_cs_argument_count (old_args);
  ipa_set_cs_argument_count (new_args, arg_count);
  new_args->jump_functions =
    duplicate_ipa_jump_func_array (old_args->jump_functions, arg_count);

  if (iinlining_processed_edges
      && bitmap_bit_p (iinlining_processed_edges, src->uid))
    bitmap_set_bit (iinlining_processed_edges, dst->uid);
}
