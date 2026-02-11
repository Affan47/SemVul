eina_hash_superfast(const char *key, int len)
{
   int hash = len, tmp;
   int rem;

   rem = len & 3;
   len >>= 2;


   for (; len > 0; len--)
     {
        hash += get16bits(key);
        tmp = (get16bits(key + 2) << 11) ^ hash;
        hash = (hash << 16) ^ tmp;
        key += 2 * sizeof (uint16_t);
        hash += hash >> 11;
     }


   switch (rem)
     {
      case 3:
        hash += get16bits(key);
        hash ^= hash << 16;
        hash ^= key[sizeof (uint16_t)] << 18;
        hash += hash >> 11;
        break;

      case 2:
        hash += get16bits(key);
        hash ^= hash << 11;
        hash += hash >> 17;
        break;

      case 1:
        hash += *key;
        hash ^= hash << 10;
        hash += hash >> 1;
     }


   hash ^= hash << 3;
   hash += hash >> 5;
   hash ^= hash << 4;
   hash += hash >> 17;
   hash ^= hash << 25;
   hash += hash >> 6;

   return hash;
}
