r_play(char *name)
{
  int fd;
  int retour = 0;

  fprintf(stderr, "Playing %s : ", name);

  if ((fd = open (name, O_RDONLY, 0)) == -1)
    {
      perror (name);
      return(0);
    }


  read (fd, (char *)audiobuf, sizeof(WaveHeader));

  if (test_wavefile (audiobuf) >= 0)
    {
      retour = recplay (fd, 0, count, WAVE_FMT, name);
    }

  if (fd != 0)
    close(fd);

  return(retour);
}
