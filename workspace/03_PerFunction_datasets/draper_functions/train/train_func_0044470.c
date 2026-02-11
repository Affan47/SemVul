get_4 (struct base64_decode_context *ctx,
       char const *restrict *in, char const *restrict in_end,
       size_t *n_non_newline)
{
  if (ctx->i == 4)
    ctx->i = 0;

  if (ctx->i == 0)
    {
      char const *t = *in;
      if (4 <= in_end - *in && memchr (t, '\n', 4) == NULL)
        {

          *in += 4;
          *n_non_newline = 4;
          return (char *) t;
        }
    }

  {

    char const *p = *in;
    while (p < in_end)
      {
        char c = *p++;
        if (c != '\n')
          {
            ctx->buf[ctx->i++] = c;
            if (ctx->i == 4)
              break;
          }
      }

    *in = p;
    *n_non_newline = ctx->i;
    return ctx->buf;
  }
}
