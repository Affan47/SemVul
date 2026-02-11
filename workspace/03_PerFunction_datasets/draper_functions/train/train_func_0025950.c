set_flags(FILE *stream, int flags) {
  switch (flags) {
    case _IONBF: stream->flags = (stream->flags & ~(BUFLINEWISE)) | NOBUF; break;
    case _IOLBF: stream->flags = (stream->flags & ~(NOBUF)) | BUFLINEWISE; break;
    case _IOFBF: stream->flags = stream->flags & ~(NOBUF | BUFLINEWISE); break;
    default: return -1;
  }
  return 0;
}
