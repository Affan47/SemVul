GetExecOutput(char *command,char *buffer,int useshell)


{ int offset = 0;
  char line[CF_BUFSIZE], *sp;
  FILE *pp;

Debug1("GetExecOutput(%s,%s)\n",command,buffer);

if (useshell)
   {
   pp = cfpopen_sh(command,"r");
   }
else
   {
   pp = cfpopen(command,"r");
   }

if (pp == NULL)
   {
   snprintf(OUTPUT,CF_BUFSIZE*2,"Couldn't open pipe to command %s\n",command);
   CfLog(cfinform,OUTPUT,"pipe");
   return false;
   }

memset(buffer,0,CF_BUFSIZE);

while (!feof(pp))
   {
   if (ferror(pp))
      {
      fflush(pp);
      break;
      }

   ReadLine(line,CF_BUFSIZE,pp);

   if (ferror(pp))
      {
      fflush(pp);
      break;
      }

   for (sp = line; *sp != '\0'; sp++)
      {
      if (*sp == '\n')
         {
         *sp = ' ';
         }
      }

   if (strlen(line)+offset > CF_BUFSIZE-10)
      {
      snprintf(OUTPUT,CF_BUFSIZE*2,"Buffer exceeded %d bytes in exec %s\n",CF_MAXVARSIZE,command);
      CfLog(cferror,OUTPUT,"");
      break;
      }

   snprintf(buffer+offset,CF_BUFSIZE,"%s ",line);
   offset += strlen(line)+1;
   }

if (offset > 0)
   {
   Chop(buffer);
   }

Debug("GetExecOutput got: [%s]\n",buffer);

cfpclose(pp);
return true;
}
