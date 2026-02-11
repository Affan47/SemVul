defineChunktype(const char *arg)
{
  if      ( strcmp("auto",  arg)   == 0 ) cdoChunkType = CHUNK_AUTO;
  else if ( strcmp("grid",  arg)   == 0 ) cdoChunkType = CHUNK_GRID;
  else if ( strcmp("lines", arg)   == 0 ) cdoChunkType = CHUNK_LINES;
  else
    {
      fprintf(stderr, "Chunk type '%s' unsupported!\n", arg);
      exit(EXIT_FAILURE);
    }
}
