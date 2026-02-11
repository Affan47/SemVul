new_parser(const char *path) {
  int fd;
  char peek;

  fd = file_peek(path, &peek);

  switch(peek) {
  case '@': return new fastq_seq_qual_parser(fd, path, &peek, 1);

  default:
    eraise(FileParserError) << "'" << path << "': "
                            << "Invalid input file. Expected fastq";
  }

  return 0;
}
