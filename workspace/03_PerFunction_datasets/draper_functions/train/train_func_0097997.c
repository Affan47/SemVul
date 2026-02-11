ArmClasses(struct Average av, char *timekey)

{ double sig;
  int code;
  struct Item *classlist = NULL, *ip;
  int i;
  char buffer[CF_BUFSIZE];
  char temp1[256], temp2[256];
  FILE *newfp;
  FILE *oldfp;
  struct flock lock;


sig = SetClasses(NAME, VALUE, av.expect, av.var, LOCALAV.expect, LOCALAV.var,
                   &classlist, timekey, &code);
SetVariable(NAME,VALUE,av.expect,sig,&classlist);

if(cfenvd_compatible)
   {
   unlink(ENVCF_NEW);
   strcpy(temp1, NAME);
   strcat(temp1, "_");
   temp2[0] = '_';
   temp2[1] = '\0';
   strcat(temp2, NAME);
   strcat(temp2, "=");

   for (i=0; i<10; i++)
      {
      lock.l_type = F_RDLCK;
      lock.l_start = 0;
      lock.l_whence = SEEK_SET;
      lock.l_len = 0;

      if ((newfp = fopen(ENVCF_NEW,"a")) == NULL)
         {
         DeleteItemList(classlist);
         return code;
         }
      if ((oldfp = fopen(ENVCF, "r")) != NULL)
         {
         if (fcntl(fileno(oldfp), F_SETLK, &lock) == -1)
            {
            Debug("Couldn't get lock, attempt %d of 10\n", i+1);
            fclose(oldfp);
            sleep(1);
            continue;
            }
         while(fgets(buffer, CF_BUFSIZE, oldfp) != NULL)
            {
            if(strstr(buffer, temp2) == NULL && strncmp(buffer, temp1, strlen(temp1)) != 0)
               {
               fprintf(newfp, "%s", buffer);
               }
            }
         fclose(oldfp);
         }

      for (ip = classlist; ip != NULL; ip=ip->next)
         {
         fprintf(newfp,"%s\n",ip->name);
         }

      fclose(newfp);

      rename(ENVCF_NEW,ENVCF);
      break;
      }
   }

DeleteItemList(classlist);

return code;
}
