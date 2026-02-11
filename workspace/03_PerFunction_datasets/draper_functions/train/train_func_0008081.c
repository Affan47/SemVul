md5_process_bytes (buffer, len, ctx)
     const void *buffer;
     size_t len;
     struct md5_ctx *ctx;
{


  if (ctx->buflen != 0)
    {
      size_t left_over = ctx->buflen;
      size_t add = 128 - left_over > len ? len : 128 - left_over;

      memcpy (&ctx->buffer[left_over], buffer, add);
      ctx->buflen += add;

      if (ctx->buflen > 64)
	{
	  md5_process_block (ctx->buffer, ctx->buflen & ~63, ctx);

	  ctx->buflen &= 63;

	  memcpy (ctx->buffer, &ctx->buffer[(left_over + add) & ~63],
		  ctx->buflen);
	}

      buffer = (const char *) buffer + add;
      len -= add;
    }


  if (len >= 64)
    {
#if !_STRING_ARCH_unaligned


# if __GNUC__ >= 2
#  define UNALIGNED_P(p) (((md5_uintptr) p) % __alignof__ (md5_uint32) != 0)
# else
#  define UNALIGNED_P(p) (((md5_uintptr) p) % sizeof (md5_uint32) != 0)
# endif
      if (UNALIGNED_P (buffer))
	while (len > 64)
	  {
	    md5_process_block (memcpy (ctx->buffer, buffer, 64), 64, ctx);
	    buffer = (const char *) buffer + 64;
	    len -= 64;
	  }
      else
#endif
	{
	  md5_process_block (buffer, len & ~63, ctx);
	  buffer = (const char *) buffer + (len & ~63);
	  len &= 63;
	}
    }


  if (len > 0)
    {
      size_t left_over = ctx->buflen;

      memcpy (&ctx->buffer[left_over], buffer, len);
      left_over += len;
      if (left_over >= 64)
	{
	  md5_process_block (ctx->buffer, 64, ctx);
	  left_over -= 64;
	  memcpy (ctx->buffer, &ctx->buffer[64], left_over);
	}
      ctx->buflen = left_over;
    }
}
