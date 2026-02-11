emitCachingMode(CacheMode c)
{
   uint32_t val;

   switch (c) {
   case CACHE_CA:

      val = 0x000;
      break;
   case CACHE_CG:
      val = 0x100;
      break;
   case CACHE_CS:
      val = 0x200;
      break;
   case CACHE_CV:

      val = 0x300;
      break;
   default:
      val = 0;
      assert(!"invalid caching mode");
      break;
   }
   code[0] |= val;
}
