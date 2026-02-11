file_open(const char *target)
{
  dvd_input_t dev;


  dev = (dvd_input_t) malloc(sizeof(*dev));
  if(dev == NULL) {
    fprintf(stderr, "libdvdread: Could not allocate memory.\n");
    return NULL;
  }


#if !defined(WIN32) && !defined(__OS2__)
  dev->fd = open(target, O_RDONLY);
#else
  dev->fd = open(target, O_RDONLY | O_BINARY);
#endif
  if(dev->fd < 0) {
    perror("libdvdread: Could not open input");
    free(dev);
    return NULL;
  }

  return dev;
}
