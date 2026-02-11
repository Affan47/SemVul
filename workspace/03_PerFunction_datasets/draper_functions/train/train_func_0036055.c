babel_get_story_length_ctx(void *ctx)
{
  struct babel_handler *bh=(struct babel_handler *) ctx;
  if (bh->blorb_mode) return bh->story_file_blorbed_extent;
  return bh->story_file_extent;
}
