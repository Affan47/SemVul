varextern(unsigned long intern, int vartype)
{
  atom *x;
  if(!oblist) ick_lose(IE778, emitlineno, (const char*) NULL);
  for (x = oblist; x < obdex; x++)
    if (x->type == vartype && (unsigned long)x->intindex == intern)
      return(x->extindex);
  if(vartype==MESH) return 0;
  ick_lose(IE778, emitlineno, (const char*) NULL);
   return 0;
}
