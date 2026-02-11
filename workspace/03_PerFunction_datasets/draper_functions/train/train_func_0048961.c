read_image(Gif_Reader *grr, Gif_Context *gfc, Gif_Image *gfi, int read_flags)

{
  uint8_t packed;

  gfi->left = gifgetunsigned(grr);
  gfi->top = gifgetunsigned(grr);
  gfi->width = gifgetunsigned(grr);
  gfi->height = gifgetunsigned(grr);
  packed = gifgetbyte(grr);
  GIF_DEBUG(("<%ux%u>", gfi->width, gfi->height));

  if (packed & 0x80) {
    int ncol = 1 << ((packed & 0x07) + 1);
    gfi->local = read_color_table(ncol, grr);
    if (!gfi->local) return 0;
    gfi->local->refcount = 1;
  }

  gfi->interlace = (packed & 0x40) != 0;


  if (read_flags & GIF_READ_COMPRESSED) {
    if (!read_compressed_image(gfi, grr, read_flags))
      return 0;
    if (read_flags & GIF_READ_UNCOMPRESSED) {
      Gif_Reader new_grr;
      make_data_reader(&new_grr, gfi->compressed, gfi->compressed_len);
      if (!uncompress_image(gfc, gfi, &new_grr))
	return 0;
    }

  } else if (read_flags & GIF_READ_UNCOMPRESSED) {
    if (!uncompress_image(gfc, gfi, grr))
      return 0;

  } else {

    uint8_t buffer[GIF_MAX_BLOCK];
    int i = gifgetbyte(grr);
    while (i > 0) {
      gifgetblock(buffer, i, grr);
      i = gifgetbyte(grr);
    }
  }

  return 1;
}
