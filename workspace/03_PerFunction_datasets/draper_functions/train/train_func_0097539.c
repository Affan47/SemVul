check_decryption_preparation (RIJNDAEL_context *ctx)
{
  if (0)
    ;
#ifdef USE_PADLOCK
  else if (ctx->use_padlock)
    {  }
#endif
  else if ( !ctx->decryption_prepared )
    {
      prepare_decryption ( ctx );
      ctx->decryption_prepared = 1;
    }
}
