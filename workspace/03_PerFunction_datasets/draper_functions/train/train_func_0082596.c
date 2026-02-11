id3_write_tag(file_t *outfile,
                  char *album_title,
                  char *artist,
                  char *title,
                  unsigned int track_number,
                  char *comment) {

  unsigned char id3[ID3_TAG_SIZE];
  unsigned char *ptr = id3 + ID3_HEADER_SIZE;
  unsigned int size = 0, bytes_left = sizeof(id3) - ID3_HEADER_SIZE;
  unsigned int len;

  if (album_title && strlen(album_title) > 0) {
    len = id3_fill_tframe(ptr, bytes_left, "TAL", 0, album_title);
    if (len == 0)
      return 0;
    bytes_left -= len; ptr += len; size += len;
  }

  if (artist && strlen(artist) > 0) {
    len = id3_fill_tframe(ptr, bytes_left, "TP1", 0, artist);
    if (len == 0)
      return 0;
    bytes_left -= len; ptr += len; size += len;
  }

  if (title && strlen(title) > 0) {
    len = id3_fill_tframe(ptr, bytes_left, "TT2", 0, title);
    if (len == 0)
      return 0;
    bytes_left -= len; ptr += len; size += len;
  }

  if (track_number > 0) {
    char tracknumber[256];
    snprintf(tracknumber, 256, "%d", track_number);
    len = id3_fill_tframe(ptr, bytes_left, "TRK", 0, tracknumber);
    if (len == 0)
      return 0;
    bytes_left -= len; ptr += len; size += len;
  }

  if (comment && strlen(comment) > 0) {
    len = id3_fill_comment(ptr, bytes_left, 0,
                           NULL,
                           comment,
                           "eng");
    if (len == 0)
      return 0;
    bytes_left -= len; ptr += len; size += len;
  }

  if (id3_fill_header(id3, sizeof(id3), size) == 0)
    return 0;

  len = file_write(outfile, id3, size + ID3_HEADER_SIZE);
  if (len != size + ID3_HEADER_SIZE)
    return 0;

  return 1;
}
