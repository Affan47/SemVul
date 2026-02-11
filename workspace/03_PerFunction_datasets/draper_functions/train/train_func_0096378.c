chunk_allocate(int bytes, const char *initial, int initial_len)
{
  if (initial_len >= bytes)
    {
      cerr<<"initialiser too long\n";
      abort();
    }

  EST_Chunk *cp = new(bytes) EST_Chunk;

  memcpy(cp->memory, initial, initial_len);

  cp->memory[initial_len] = '\0';

  return (EST_ChunkPtr)cp;
}
