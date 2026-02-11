IsIntIn(struct Rlist *list,int i)

{ struct Rlist *rp;
  char s[CF_SMALLBUF];

snprintf(s,CF_SMALLBUF-1,"%d",i);

if (list == NULL)
   {
   return false;
   }

for (rp = list; rp != NULL; rp=rp->next)
   {
   if (rp->type != CF_SCALAR)
      {
      continue;
      }

   if (strcmp(s,rp->item) == 0)
      {
      return true;
      }
   }

return false;
}
