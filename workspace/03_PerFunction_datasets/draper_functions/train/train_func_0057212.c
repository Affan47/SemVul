xsh_frame_inv( cpl_frame* in, const char *filename,
  xsh_instrument* instr)
{
  xsh_pre *pre = NULL;
  cpl_frame *result = NULL;
  const char* tag = "INV_PRE";

  XSH_ASSURE_NOT_NULL( in);
  XSH_ASSURE_NOT_NULL( instr);

  check( pre = xsh_pre_load( in, instr));
  check( xsh_pre_multiply_scalar( pre, -1.0));
  check( result = xsh_pre_save( pre, filename, tag, 1));
  check( cpl_frame_set_tag( result, tag));

  cleanup:
    if (cpl_error_get_code() != CPL_ERROR_NONE){
      xsh_free_frame( &result);
    }
   xsh_pre_free( &pre);
   return result;
}
