CheckTimeZone()

{ struct Item *ip;
  char tz[CF_MAXVARSIZE];

if (VTIMEZONE == NULL)
   {
   CfLog(cferror,"Program does not define a timezone","");
   return;
   }

for (ip = VTIMEZONE; ip != NULL; ip=ip->next)
   {
#ifdef OLDNT
      tzset();
      strcpy(tz,timezone());
#else
#ifndef AOS
#ifndef SUN4

   tzset();
   strcpy(tz,tzname[0]);

#else

   if ((tloc = time((time_t *)NULL)) == -1)
      {
      printf("Couldn't read system clock\n\n");
      }
   strcpy(tz,localtime(&tloc)->tm_zone);

#endif
#endif
#endif

   if (TZCheck(tz,ip->name))
      {
      return;
      }
   }

snprintf(OUTPUT,CF_BUFSIZE*2,"Time zone was %s which is not in the list of acceptable values",tz);
CfLog(cferror,OUTPUT,"");
}
