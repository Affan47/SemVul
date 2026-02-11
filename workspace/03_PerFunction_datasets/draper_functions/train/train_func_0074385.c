Rlist2String(struct Rlist *list,char *sep)

{ char line[CF_BUFSIZE];
  struct Rlist *rp;

line[0] = '\0';

for(rp = list; rp != NULL; rp=rp->next)
   {
   strcat(line,(char *)rp->item);

   if (rp->next)
      {
      strcat(line,sep);
      }
   }

return strdup(line);
}
