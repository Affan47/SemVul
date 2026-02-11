getFollowing(const GroveImpl *grove,
				     const Chunk *&f,
				     unsigned long &i) const
{


  const Chunk *p = CharsChunk::after();
  while (p == grove->completeLimit())
    if (!grove->waitForMoreNodes())
      return accessTimeout;
  if (p->origin != origin)
    return accessNull;
  i = size;
  f = p;
  return accessOK;
}
