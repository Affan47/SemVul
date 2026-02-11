DeleteSeveralLines (struct Item **filestart,char *string)


{ struct Item *ip, *ip_prev;
  int ctr, N = -99, done = false;

Debug2("DeleteNLines(list,%s)\n",string);

sscanf(string,"%d", &N);

if (N < 1)
   {
   snprintf(OUTPUT,CF_BUFSIZE*2,"Illegal number value in DeleteNLines: %s\n",string);
   CfLog(cferror,OUTPUT,"");
   return false;
   }


if (CURRENTLINEPTR == NULL)
   {
   CfLog(cferror,"File line-pointer undefined during editfile action\n","");
   return true;
   }

for (ip_prev = *filestart; ip_prev && ip_prev->next != CURRENTLINEPTR; ip_prev=ip_prev->next)
   {
   }

ctr = 1;

for (ip = CURRENTLINEPTR; ip != NULL; ip = CURRENTLINEPTR)
   {
   if (ip->name == NULL)
      {
      continue;
      }

   if (EDABORTMODE && ItemMatchesRegEx(ip->name,VEDITABORT))
      {
      Verbose("Aborting search, regex %s matches line\n",VEDITABORT);
      return false;
      }

   if (ctr == N)
      {
      EditVerbose("Terminating line: %s (Done)\n",ip->name);
      done = true;
      }

   EditVerbose("Delete line %s\n",ip->name);
   NUMBEROFEDITS++;
   CURRENTLINEPTR = ip->next;

   if (ip_prev == NULL)
      {
      *filestart = ip->next;
      }
   else
      {
      ip_prev->next = ip->next;
      }

   free (ip->name);
   free ((char *)ip);
   ctr++;

   if (done)
      {
      break;
      }
   }

if (ctr-1 < N)
   {
   snprintf(OUTPUT,CF_BUFSIZE*2,"DeleteNLines deleted only %d lines (not %d)\n",ctr-1,N);
   CfLog(cfsilent,OUTPUT,"");
   }

return true;
}
