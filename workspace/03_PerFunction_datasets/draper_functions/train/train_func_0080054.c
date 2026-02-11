info_getN(cchar **files, int NF, cchar **keys, int NK)
{
   char     *ppk, *ppv, **keyvals;
   int      contx = 0, cc, ii, ff, kk;
   char     command[10000];

   cc = (1 + NF * NK) * sizeof(char *);
   keyvals = (char **) zmalloc(cc,"info_getN");
   memset(keyvals,0,cc);

   strcpy(command,"exiftool -m -s2 -fast2");

   for (kk = 0; kk < NK; kk++)
      strncatv(command,9999," -",keys[kk],null);

   for (ff = 0; ff < NF; ff++)
      strncatv(command,9999," \"",files[ff],"\"",null);

   ff = NF;

   while ((ppk = command_output(contx,command)))
   {
      if (NF > 1)
      {
         if (strnEqu(ppk,"========",8))
         {
            for (ff = 0; ff < NF; ff++)
               if (strstr(ppk+8,files[ff])) break;
            zfree(ppk);
            continue;
         }

         if (ff == NF) continue;
      }

      else ff = 0;

      for (kk = 0; kk < NK; kk++)
      {
         cc = strlen(keys[kk]);
         if (strncasecmp(ppk,keys[kk],cc)) continue;
         ppv = ppk + cc;
         while (*ppv && *ppv == ' ') ppv++;
         if (strncmp(ppv,": ",2)) continue;
         ppv += 2;
         if (strlen(ppv) < 1) continue;
         if (strlen(ppv) > 999) ppv[999] = 0;
         ii = NK * ff + kk;
         keyvals[ii] = strdupz(ppv,0,"info_getN");
         break;
      }

      zfree(ppk);
   }

   return keyvals;
}
