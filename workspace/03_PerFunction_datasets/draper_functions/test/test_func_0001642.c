lib3ds_shadow_read(Lib3dsShadow *shadow, Lib3dsIo *io)
{
  Lib3dsChunk c;

  if (!lib3ds_chunk_read(&c, io)) {
    return(LIB3DS_FALSE);
  }

  switch (c.chunk) {
    case LIB3DS_SHADOW_MAP_SIZE:
      {
        shadow->map_size=lib3ds_io_read_intw(io);
      }
      break;
    case LIB3DS_LO_SHADOW_BIAS:
      {
          shadow->lo_bias=lib3ds_io_read_float(io);
      }
      break;
    case LIB3DS_HI_SHADOW_BIAS:
      {
        shadow->hi_bias=lib3ds_io_read_float(io);
      }
      break;
    case LIB3DS_SHADOW_SAMPLES:
      {
        shadow->samples=lib3ds_io_read_intw(io);
      }
      break;
    case LIB3DS_SHADOW_RANGE:
      {
        shadow->range=lib3ds_io_read_intd(io);
      }
      break;
    case LIB3DS_SHADOW_FILTER:
      {
        shadow->filter=lib3ds_io_read_float(io);
      }
      break;
    case LIB3DS_RAY_BIAS:
      {
        shadow->ray_bias=lib3ds_io_read_float(io);
      }
      break;
  }

  return(LIB3DS_TRUE);
}
