lto_get_out_decl_state (void)
{
  return VEC_last (lto_out_decl_state_ptr, decl_state_stack);
}
