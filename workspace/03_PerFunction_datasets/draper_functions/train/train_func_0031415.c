clone_metadata_t(metadata_t const * const meta)
{
  metadata_t *clone = new_metadata_t();

  if (meta->artist != NULL)
    clone->artist = g_strdup(meta->artist);
  if (meta->title != NULL)
    clone->title = g_strdup(meta->title);
  if (meta->album != NULL)
    clone->album = g_strdup(meta->album);
  clone->year = meta->year;
  if (meta->genre != NULL)
    clone->genre = g_strdup(meta->genre);
  clone->length = meta->length;
  clone->size = meta->size;
  if (meta->codec != NULL)
    clone->codec = g_strdup(meta->codec);
  clone->trackno = meta->trackno;
  clone->protect = meta->protect;
  if (meta->filename != NULL)
    clone->filename = g_strdup(meta->filename);
  if (meta->path != NULL)
    clone->path = g_strdup(meta->path);
  if (meta->folder != NULL)
    clone->folder = g_strdup(meta->folder);
  return clone;
}
