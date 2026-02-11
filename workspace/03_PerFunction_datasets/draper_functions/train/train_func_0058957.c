alclfile(name)
char *name;
   {
   struct lfile *p;

   p = alloc(sizeof(struct lfile));
   if (!p)
      tsyserr("not enough memory for file list");
   p->lf_link = NULL;
   p->lf_name = salloc(name);
   return p;
   }
