emitCachingMode(CacheMode c, const int pos)
{
   uint8_t n;

   switch (c) {
   case CACHE_CA:

      n = 0;
      break;
   case CACHE_CG:
      n = 1;
      break;
   case CACHE_CS:
      n = 2;
      break;
   case CACHE_CV:

      n = 3;
      break;
   default:
      n = 0;
      assert(!"invalid caching mode");
      break;
   }
   code[pos / 32] |= n << (pos % 32);
}
