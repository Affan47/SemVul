GetSetuidLog()

{ struct Item *filetop = NULL;
  struct Item *ip;
  FILE *fp;
  char *sp;

if (!IsPrivileged())
   {
   return;
   }

if ((fp = fopen(VSETUIDLOG,"r")) == NULL)
   {
   }
else
   {
   while (!feof(fp))
      {
      ReadLine(VBUFF,CF_BUFSIZE,fp);

      if (strlen(VBUFF) == 0)
         {
         continue;
         }

      if ((ip = (struct Item *)malloc (sizeof(struct Item))) == NULL)
         {
         perror("malloc");
         FatalError("GetSetuidList() couldn't allocate memory #1");
         }

      if ((sp = malloc(strlen(VBUFF)+2)) == NULL)
         {
         perror("malloc");
         FatalError("GetSetuidList() couldn't allocate memory #2");
         }

      if (filetop == NULL)
         {
         VSETUIDLIST = filetop = ip;
         }
      else
         {
         filetop->next = ip;
         }

      Debug2("SETUID-LOG: %s\n",VBUFF);

      strcpy(sp,VBUFF);
      ip->name = sp;
      ip->next = NULL;
      filetop = ip;
      }

   fclose(fp);
   }

}
