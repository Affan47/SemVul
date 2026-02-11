BuildClassEnvironment()

{ struct Item *ip;
  int size = 0;
  char file[CF_BUFSIZE], *sp;
  FILE *fp;
  DB *dbp;
  DB_ENV *dbenv = NULL;

Debug("(BuildClassEnvironment)\n");

snprintf(ALLCLASSBUFFER,CF_BUFSIZE,"%s=",CF_ALLCLASSESVAR);

if (!IsPrivileged())
   {
   Verbose("\n(Non privileged user...)\n\n");

   if ((sp = getenv("HOME")) == NULL)
      {
      FatalError("You do not have a HOME variable pointing to your home directory");
      }

   snprintf(file,CF_BUFSIZE,"%s/.cfagent/allclasses",sp);
   }
else
   {
   snprintf(file,CF_BUFSIZE,"%s/state/allclasses",WORKDIR);
   }


if ((fp = fopen(file,"w")) == NULL)
   {
   CfLog(cfinform,"Could not open allclasses cache file","");
   return;
   }

for (ip = VHEAP; ip != NULL; ip=ip->next)
   {
   if (IsDefinedClass(ip->name))
      {
      if ((size += strlen(ip->name)) > CF_ALLCLASSSIZE - CF_BUFFERMARGIN)
         {
         Verbose("Class buffer overflowed, dumping class environment for modules\n");
         Verbose("This would probably crash the exec interface on most machines\n");
         }
      else
         {
         size++;
         strcat(ALLCLASSBUFFER,ip->name);
         strcat(ALLCLASSBUFFER,":");
         }

      fprintf(fp,"%s\n",ip->name);
      }
   }

for (ip = VALLADDCLASSES; ip != NULL; ip=ip->next)
   {
   if (IsDefinedClass(ip->name))
      {
      if ((size += strlen(ip->name)) > 4*CF_BUFSIZE - CF_BUFFERMARGIN)
         {
         Verbose("Class buffer overflowed, dumping class environment for modules\n");
         Verbose("This would probably crash the exec interface on most machines\n");
         }
      else
         {
         size++;
         strcat(ALLCLASSBUFFER,ip->name);
         strcat(ALLCLASSBUFFER,":");
         }

      fprintf(fp,"%s\n",ip->name);
      }
   }

Debug2("---\nENVIRONMENT: %s\n---\n",ALLCLASSBUFFER);

if (USEENVIRON)
   {
   if (putenv(ALLCLASSBUFFER) == -1)
      {
      perror("putenv");
      }
   }

fclose(fp);
}
