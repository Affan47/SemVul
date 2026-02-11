MurmurHash64B ( const void * key, std::size_t len, uint64_t seed )
{
  const unsigned int m = 0x5bd1e995;
  const int r = 24;

  unsigned int h1 = seed ^ len;
  unsigned int h2 = 0;

#if defined(__arm) || defined(__arm__)
  size_t ksize = sizeof(unsigned int);
  const unsigned char * data = (const unsigned char *)key;
#else
  const unsigned int * data = (const unsigned int *)key;
#endif

  unsigned int k1, k2;
  while(len >= 8)
  {
#if defined(__arm) || defined(__arm__)
    memcpy(&k1, data, ksize);
    data += ksize;
    memcpy(&k2, data, ksize);
    data += ksize;
#else
    k1 = *data++;
    k2 = *data++;
#endif

    k1 *= m; k1 ^= k1 >> r; k1 *= m;
    h1 *= m; h1 ^= k1;
    len -= 4;

    k2 *= m; k2 ^= k2 >> r; k2 *= m;
    h2 *= m; h2 ^= k2;
    len -= 4;
  }

  if(len >= 4)
  {
#if defined(__arm) || defined(__arm__)
    memcpy(&k1, data, ksize);
    data += ksize;
#else
    k1 = *data++;
#endif
    k1 *= m; k1 ^= k1 >> r; k1 *= m;
    h1 *= m; h1 ^= k1;
    len -= 4;
  }

  switch(len)
  {
  case 3: h2 ^= ((unsigned char*)data)[2] << 16;
  case 2: h2 ^= ((unsigned char*)data)[1] << 8;
  case 1: h2 ^= ((unsigned char*)data)[0];
      h2 *= m;
  };

  h1 ^= h2 >> 18; h1 *= m;
  h2 ^= h1 >> 22; h2 *= m;
  h1 ^= h2 >> 17; h1 *= m;
  h2 ^= h1 >> 19; h2 *= m;

  uint64_t h = h1;

  h = (h << 32) | h2;

  return h;
}
