readstream(struct ASPK *stream) {
  while (stream->bitpos >= 8) {
    if (stream->input>=stream->iend) return 0;
    stream->hash = (stream->hash << 8) | *stream->input;
    stream->input++;
    stream->bitpos -= 8;
  }
  return 1;
}
