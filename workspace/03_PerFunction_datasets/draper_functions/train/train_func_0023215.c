duplogenlist(logen_list *s, logen_list *d, char *name)
{
   logen_list *g;

   d=addlogen(d,name);
   d->TYPE=s->TYPE;
   d->VALUE.LIST=NULL;
   if (s->TYPE==GENTYPE_LIST) {
      for (g=s->VALUE.LIST; g; g=g->NEXT)
         d->VALUE.LIST=duplogenlist(g, d->VALUE.LIST, NULL);
      d->VALUE.LIST=(logen_list *)reverse((chain_list *)d->VALUE.LIST);
   } else
      d->VALUE=s->VALUE;

   return d;
}
