srcAddr16(const ValueRef& src, bool adj, const int pos)
{
   assert(src.get());

   int32_t offset = SDATA(src).offset;

   assert(!adj || src.get()->reg.size <= 4);
   if (adj)
      offset /= src.get()->reg.size;

   assert(offset <= 0x7fff && offset >= (int32_t)-0x8000 && (pos % 32) <= 16);

   if (offset < 0)
      offset &= adj ? (0xffff >> (src.get()->reg.size >> 1)) : 0xffff;

   code[pos / 32] |= offset << (pos % 32);
}
