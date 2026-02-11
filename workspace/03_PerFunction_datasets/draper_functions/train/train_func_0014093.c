lookup(hash_ptr *ht, SV *sv, void *tag)
{unsigned hash = ((unsigned long) sv) % MAX_HASH;
 hash_ptr p = ht[hash];
 while (p)
  {
   if (p->sv == sv)
    {char *old = p->tag;
     p->tag = tag;
     return old;
    }
   p = p->link;
  }
 if ((p = pile))
  pile = p->link;
 else
  p = (hash_ptr) malloc(sizeof(struct hash_s));
 p->link  = ht[hash];
 p->sv    = sv;
 p->tag   = tag;
 ht[hash] = p;
 return NULL;
}
