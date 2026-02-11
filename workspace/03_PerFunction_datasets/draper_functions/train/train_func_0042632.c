LogChecksumChange(char *file)

{ FILE *fp;
 char fname[CF_BUFSIZE],timebuf[CF_MAXVARSIZE];
  time_t now = time(NULL);


snprintf(fname,CF_BUFSIZE,"%s/state/file_hash_event_history",CFWORKDIR);

if ((fp = fopen(fname,"a")) == NULL)
   {
   CfLog(cferror,"Could not write to the change log","");
   return;
   }

snprintf(timebuf,CF_MAXVARSIZE-1,"%s",ctime(&now));
Chop(timebuf);
fprintf(fp,"%s,%s\n",timebuf,file);

fclose(fp);
}
