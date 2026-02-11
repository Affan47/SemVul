del_styleattr(APTR data)
{
#if DEBUG_ATTR
   fprintf(stderr, DHL "   del_styleattr %s (mci=%d)\n",
         var->name, var->macro_id);
#endif
   ufreestr(((HSCSTYLE*)data)->name);
   ufreestr(((HSCSTYLE*)data)->value);
   ufree(data);
}
