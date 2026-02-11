read_link(struct sar_file *out, mode_t mode)
{
  char path[WP_MAX + 1];
  enum fsclass class;
  uint16_t size = 0;


  class = out->nsclass & N_FILE;
  switch(class) {
    uint8_t  size_byte;
    uint16_t size_kilo;

  case(N_FBYTE):
    xcrc_read(out, &size_byte, sizeof(size_byte));
    size = size_byte;
    break;
  case(N_FKILO):
    xcrc_read(out, &size_kilo, sizeof(size_kilo));
    size = le16toh(size_kilo);
    break;
  case(N_FGIGA):
  case(N_FHUGE):
    errx(EXIT_FAILURE, "link size too large for \"%s\"", out->wp);
  }
  out->size = size;


  if(size > WP_MAX)
    errx(EXIT_FAILURE, "path size exceeded");
  xcrc_read(out, path, size);
  path[size] = '\0';


  out->link = strdup(path);
  if(!out->list_only && symlink(path, out->wp) < 0)
    warn("cannot create symlink \"%s\" to \"%s\"", out->wp, path);
}
