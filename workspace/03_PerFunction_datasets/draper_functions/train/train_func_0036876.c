fog_read(Lib3dsFog *fog, Lib3dsIo *io)
{
  Lib3dsChunk c;
  Lib3dsWord chunk;

  if (!lib3ds_chunk_read_start(&c, LIB3DS_FOG, io)) {
    return(LIB3DS_FALSE);
  }
  fog->near_plane = lib3ds_io_read_float(io);
  fog->near_density=lib3ds_io_read_float(io);
  fog->far_plane=lib3ds_io_read_float(io);
  fog->far_density=lib3ds_io_read_float(io);
  lib3ds_chunk_read_tell(&c, io);

  while ((chunk=lib3ds_chunk_read_next(&c, io))!=0) {
    switch (chunk) {
      case LIB3DS_LIN_COLOR_F:
        {
          int i;
          for (i=0; i<3; ++i) {
            fog->col[i]=lib3ds_io_read_float(io);
          }
        }
        break;
      case LIB3DS_COLOR_F:
        break;
      case LIB3DS_FOG_BGND:
        {
          fog->fog_background=LIB3DS_TRUE;
        }
        break;
      default:
        lib3ds_chunk_unknown(chunk);
    }
  }

  lib3ds_chunk_read_end(&c, io);
  return(LIB3DS_TRUE);
}
