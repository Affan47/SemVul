new_styleattr(CONSTRPTR name, CONSTRPTR value) {
   HSCSTYLE *newvar = (HSCSTYLE*)umalloc(sizeof(HSCSTYLE));

#if DEBUG_ATTR
   fprintf(stderr, DHL "   new_styleattr\n");
#endif

   if(newvar) {
      newvar->name  = strclone(name);
      newvar->value = strclone(value);
   }
   return newvar;
}
