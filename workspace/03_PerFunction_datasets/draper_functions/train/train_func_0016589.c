iobfileopen(FILE *istream)
{
  IOBFILE *iobf;

  if (istream == NULL) {
    return NULL;
  }

  iobf = calloc(1, sizeof(IOBFILE));
  iobf->istream = istream;
  iobf->fd = fileno(istream);
  iobf->ungetc = EOF;

  if (iobf->fd >= 0) {

    if (lseek(iobf->fd, 0, SEEK_CUR) != -1 &&
	!isatty(iobf->fd)) {
      iobf->can_seek = -1;
    }


#if SETVBUF_REVERSED
    setvbuf(istream, _IONBF, NULL, 0);
#else
    setvbuf(istream, NULL, _IONBF, 0);
#endif
#if HAVE_FCNTL
    iobf->fflags = fcntl(iobf->fd, F_GETFL);
    if (iobf->fflags != -1 && (iobf->fflags & o_nonblock)) {
      iobf->fflags &= ~o_nonblock;
      if (fcntl(iobf->fd, F_SETFL, iobf->fflags) < 0) {
	fprintf(stderr, "iobfileopen(): unable to clear O_NONBLOCK: \"%s\"\n",
		strerror(errno));
      }
    }
  } else {
    iobf->fflags = -1;
#endif
  }

  iob_init_buffer(&iobf->ioblist);

  iobf->ungetc    = EOF;

#if DEBUG
  n_fileopen++;
  if (n_fileopen > max_fileopen) {
    max_fileopen = n_fileopen;
    fprintf(stderr, "max fileopen: %d\n", max_fileopen);
  }
#endif

  return iobf;
}
