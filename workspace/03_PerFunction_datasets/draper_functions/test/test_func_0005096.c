AAC_Reader_del(AACReader * read)
{
  if (!read)
    return;
  AAC_disconnect_from_http_and_free(read);
#ifdef DONT_USE_TERMINAL_MODULE_API
  if (read->dm)
    gf_dm_del(read->dm);
  read->dm = NULL;
#endif
  if (read->icy_name)
    gf_free(read->icy_name);
  if (read->icy_genre)
    gf_free(read->icy_genre);
  if (read->icy_track_name)
    gf_free(read->icy_track_name);
  read->icy_name = read->icy_genre = read->icy_track_name = NULL;
  if (read->stream)
    fclose(read->stream);
  if (read->data)
    gf_free(read->data);
  read->data = NULL;
  read->stream = NULL;
  gf_free( read );
}
