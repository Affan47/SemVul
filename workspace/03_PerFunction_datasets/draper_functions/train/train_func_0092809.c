InstallItem (struct Item **liststart,char *itemstring,char *classes,int ifelapsed,int expireafter)

{ struct Item *ip, *lp;
  char *sp,*spe = NULL;

if (!PARSING && (ACTION == editfiles))
   {
   snprintf(OUTPUT,CF_BUFSIZE,"Appending [%s]\n",itemstring);
   CfLog(cfinform,OUTPUT,"");
   }
else
   {
   EditVerbose("Appending [%s]\n",itemstring);
   }


if ((ip = (struct Item *)malloc(sizeof(struct Item))) == NULL)
   {
   CfLog(cferror,"","malloc");
   FatalError("");
   }

if ((sp = malloc(strlen(itemstring)+CF_EXTRASPC)) == NULL)
   {
   CfLog(cferror,"","malloc");
   FatalError("");
   }

if (*liststart == NULL)
   {
   *liststart = ip;
   }
else
   {
   for (lp = *liststart; lp->next != NULL; lp=lp->next)
      {
      }

   lp->next = ip;
   }

if ((classes!= NULL) && (spe = malloc(strlen(classes)+2)) == NULL)
   {
   CfLog(cferror,"","malloc");
   FatalError("");
   }

strcpy(sp,itemstring);

if (PIFELAPSED != -1)
   {
   ip->ifelapsed = PIFELAPSED;
   }
else
   {
   ip->ifelapsed = ifelapsed;
   }

if (PEXPIREAFTER != -1)
   {
   ip->expireafter = PEXPIREAFTER;
   }
else
   {
   ip->expireafter = expireafter;
   }

ip->name = sp;
ip->next = NULL;

if (classes != NULL)
   {
   strcpy(spe,classes);
   ip->classes = spe;
   }
else
   {
   ip->classes = NULL;
   }

ip->logaudit = AUDITP;
ip->audit = AUDITPTR;
ip->lineno = LINENUMBER;

NUMBEROFEDITS++;
}
