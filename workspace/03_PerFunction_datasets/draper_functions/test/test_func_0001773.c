in_state_cdata(statemachine_ctx *ctx, int start, char chr, int end)
{
  htmlparser_ctx *html = CAST(htmlparser_ctx *, ctx->user);
  assert(html != NULL);

  if (html->in_js)
    jsparser_parse_chr(html->jsparser, chr);
}
