is_builtin(gptr)
struct gentry *gptr;
   {
   struct implement *iptr;

   if (!(gptr->flag & F_StrInv))
      return 0;
   if (gptr->flag & F_Builtin)
      return gptr->val.builtin->prefix;
   iptr = db_ilkup(gptr->name, bhash);
   if (iptr == NULL)
      return NULL;
   bi_proc(gptr->name, iptr);
   return iptr->prefix;
   }
