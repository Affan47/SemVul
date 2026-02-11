sha512_process_bytes (const void *buffer, size_t len, struct sha512_ctx *ctx)
{


  if (ctx->buflen != 0)
    {
      size_t left_over = ctx->buflen;
      size_t add = 256 - left_over > len ? len : 256 - left_over;

      memcpy (&((char *) ctx->buffer)[left_over], buffer, add);
      ctx->buflen += add;

      if (ctx->buflen > 128)
	{
	  sha512_process_block (ctx->buffer, ctx->buflen & ~63, ctx);

	  ctx->buflen &= 127;

	  memcpy (ctx->buffer,
		  &((char *) ctx->buffer)[(left_over + add) & ~127],
		  ctx->buflen);
	}

      buffer = (const char *) buffer + add;
      len -= add;
    }


  if (len >= 128)
    {
#if !_STRING_ARCH_unaligned
# define alignof(type) offsetof (struct { char c; type x; }, x)
# define UNALIGNED_P(p) (((size_t) p) % alignof (uint64_t) != 0)
      if (UNALIGNED_P (buffer))
	while (len > 128)
	  {
	    sha512_process_block (memcpy (ctx->buffer, buffer, 128), 128, ctx);
	    buffer = (const char *) buffer + 128;
	    len -= 128;
	  }
      else
#endif
	{
	  sha512_process_block (buffer, len & ~127, ctx);
	  buffer = (const char *) buffer + (len & ~127);
	  len &= 127;
	}
    }


  if (len > 0)
    {
      size_t left_over = ctx->buflen;

      memcpy (&((char *) ctx->buffer)[left_over], buffer, len);
      left_over += len;
      if (left_over >= 128)
	{
	  sha512_process_block (ctx->buffer, 128, ctx);
	  left_over -= 128;
	  memcpy (ctx->buffer, &ctx->buffer[16], left_over);
	}
      ctx->buflen = left_over;
    }
}
