output_struct_function_base (struct output_block *ob, struct function *fn)
{
  struct bitpack_d bp;
  unsigned i;
  tree t;


  stream_write_tree (ob, fn->static_chain_decl, true);
  stream_write_tree (ob, fn->nonlocal_goto_save_area, true);


  streamer_write_hwi (ob, vec_safe_length (fn->local_decls));
  FOR_EACH_VEC_SAFE_ELT (fn->local_decls, i, t)
    stream_write_tree (ob, t, true);


  streamer_write_uhwi (ob, fn->curr_properties);


  bp = bitpack_create (ob->main_stream);
  bp_pack_value (&bp, fn->is_thunk, 1);
  bp_pack_value (&bp, fn->has_local_explicit_reg_vars, 1);
  bp_pack_value (&bp, fn->returns_pcc_struct, 1);
  bp_pack_value (&bp, fn->returns_struct, 1);
  bp_pack_value (&bp, fn->can_throw_non_call_exceptions, 1);
  bp_pack_value (&bp, fn->can_delete_dead_exceptions, 1);
  bp_pack_value (&bp, fn->always_inline_functions_inlined, 1);
  bp_pack_value (&bp, fn->after_inlining, 1);
  bp_pack_value (&bp, fn->stdarg, 1);
  bp_pack_value (&bp, fn->has_nonlocal_label, 1);
  bp_pack_value (&bp, fn->calls_alloca, 1);
  bp_pack_value (&bp, fn->calls_setjmp, 1);
  bp_pack_value (&bp, fn->va_list_fpr_size, 8);
  bp_pack_value (&bp, fn->va_list_gpr_size, 8);


  stream_output_location (ob, &bp, fn->function_start_locus);
  stream_output_location (ob, &bp, fn->function_end_locus);

  streamer_write_bitpack (&bp);
}
