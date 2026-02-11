pushdef(d)
cdefn *d;
   {
   buffer *b;

   d->inuse = 1;
   b = bfree;
   if (b == NULL)
      b = (buffer *)alloc(sizeof(buffer));
   else
      bfree = b->prev;
   b->prev = bstack;
   b->defn = d;
   b->ptr = bnxt;
   b->stop = bstop;
   b->lim = blim;
   bstack = b;
   bnxt = bstop = d->s + d->nlen;
   blim = bnxt + d->vlen;
   }
