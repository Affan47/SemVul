new_bregexp(const char *motif)
{
   Dmsg0(500, "bregexp: creating new bregexp object\n");
   BREGEXP *self = (BREGEXP *)bmalloc(sizeof(BREGEXP));
   memset(self, 0, sizeof(BREGEXP));

   if (!self->extract_regexp(motif)) {
      Dmsg0(100, "bregexp: extract_regexp error\n");
      free_bregexp(self);
      return NULL;
   }

   self->result = get_pool_memory(PM_FNAME);
   self->result[0] = '\0';

   return self;
}
