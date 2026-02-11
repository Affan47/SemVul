textureMask(TexInstruction *tex)
{
   Value *def[4];
   int c, k, d;
   uint8_t mask = 0;

   for (d = 0, k = 0, c = 0; c < 4; ++c) {
      if (!(tex->tex.mask & (1 << c)))
         continue;
      if (tex->getDef(k)->refCount()) {
         mask |= 1 << c;
         def[d++] = tex->getDef(k);
      }
      ++k;
   }
   tex->tex.mask = mask;

   for (c = 0; c < d; ++c)
      tex->setDef(c, def[c]);
   for (; c < 4; ++c)
      tex->setDef(c, NULL);
}
