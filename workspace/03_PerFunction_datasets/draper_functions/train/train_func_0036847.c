cfg_bitMerge(
  TOPO_MAP *m,
  TOPO_MAP *t)
{
   int i;

   for (i=0;i<(int)MAX_BIT_IDX;i++) {
      m->bits[i] |= t->bits[i];
      if (0 != m->bits[i] && i > m->msw)
         m->msw = i;
      }
}
