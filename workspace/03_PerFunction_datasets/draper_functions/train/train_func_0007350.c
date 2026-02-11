solid_bgnd_read(Lib3dsBackground *background, Lib3dsIo *io)
{
  Lib3dsChunk c;
  Lib3dsWord chunk;
  Lib3dsBool have_lin=LIB3DS_FALSE;

  if (!lib3ds_chunk_read_start(&c, LIB3DS_SOLID_BGND, io)) {
    return(LIB3DS_FALSE);
  }

  while ((chunk=lib3ds_chunk_read_next(&c, io))!=0) {
    switch (chunk) {
      case LIB3DS_LIN_COLOR_F:
        lib3ds_io_read_rgb(io, background->solid.col);
        have_lin=LIB3DS_TRUE;
        break;
      case LIB3DS_COLOR_F:
        lib3ds_io_read_rgb(io, background->solid.col);
        break;
      default:
        lib3ds_chunk_unknown(chunk);
    }
  }

  lib3ds_chunk_read_end(&c, io);
  return(LIB3DS_TRUE);
}
