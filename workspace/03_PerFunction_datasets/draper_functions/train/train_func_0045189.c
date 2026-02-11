getlogen(logen_list *ptgen, char *name)
{
   name=namealloc(name);
   while (ptgen) {
      if (ptgen->NAME==name)
         return ptgen;
      ptgen=ptgen->NEXT;
   }
   return NULL;
}
