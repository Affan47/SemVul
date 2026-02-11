next_token(
   struct tgsi_parse_context *ctx,
   void *token )
{
   assert( !tgsi_parse_end_of_tokens( ctx ) );
   copy_token(token, &ctx->Tokens[ctx->Position]);
   ctx->Position++;
}
