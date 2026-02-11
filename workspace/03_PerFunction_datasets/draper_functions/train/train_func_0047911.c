whirlpool_final_bugemu (void *ctx)
{
  whirlpool_context_t *context = ctx;
  unsigned int i;


  whirlpool_add_bugemu (context, NULL, 0);


  context->bctx.buf[context->bugemu.count++] = 0x80;

  if (context->bugemu.count > 32)
    {

      while (context->bugemu.count < 64)
	context->bctx.buf[context->bugemu.count++] = 0;
      whirlpool_add_bugemu (context, NULL, 0);
    }
  while (context->bugemu.count < 32)
    context->bctx.buf[context->bugemu.count++] = 0;


  memcpy (context->bctx.buf + context->bugemu.count,
          context->bugemu.length, 32);
  context->bugemu.count += 32;
  whirlpool_add_bugemu (context, NULL, 0);

  block_to_buffer (context->bctx.buf, context->hash_state, i);
}
