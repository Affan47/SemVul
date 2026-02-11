gif_read_error(Gif_Context *gfc, int is_error, const char *text)
{
  gfc->stream->errors++;
  if (gfc->handler)
      gfc->handler(is_error, text, gfc->stream->nimages, gfc->handler_thunk);
}
