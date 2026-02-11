write_songlib_t(FILE *fh, songlib_t *songlib)
{
  song_t *seeker = *(songlib->lib);
  int songcount = song_lib_count(*songlib);

  fprintf(fh, "{\n");
  fprintf(fh, "songcount = %d\n", songcount);
  fprintf(fh, "list = \n");
  fprintf(fh, "[\n");
  while (seeker)
    {
      seeker->restore_time = seeker->it->get_timepos(seeker->it);

  _cfsml_write_song_t(fh, seeker);
  fprintf(fh, "\n");

      seeker = seeker->next;
    }
  fprintf(fh, "]\n");
  fprintf(fh, "}\n");
}
