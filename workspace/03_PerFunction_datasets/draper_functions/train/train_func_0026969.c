GetLockName(char *lockname,char *locktype,char *base,struct Rlist *params)

{ struct Rlist *rp;
 int max_sample, count = 0;

for (rp = params; rp != NULL; rp=rp->next)
   {
   count++;
   }

if (count)
   {
   max_sample = CF_BUFSIZE / (2*count);
   }
else
   {
   max_sample = 0;
   }

strncpy(lockname,locktype,CF_BUFSIZE/10);
strcat(lockname,"_");
strncat(lockname,base,CF_BUFSIZE/10);
strcat(lockname,"_");

for (rp = params; rp != NULL; rp=rp->next)
   {
   strncat(lockname,(char *)rp->item,max_sample);
   }
}
