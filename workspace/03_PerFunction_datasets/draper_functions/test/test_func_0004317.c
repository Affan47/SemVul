ftp_checkfile (char *urltype, char *infile, char *outfile1)
{
  char newinfile[MAXLEN];
  FILE *ftpfile;
  FILE *command;
  int sock;


  strcpy(urltype,"ftp://");

  if (strlen(outfile1)) {


    if (!strncmp(outfile1, "file://", 7) )
       strcpy(netoutfile,outfile1+7);
    else
       strcpy(netoutfile,outfile1);

    if (!strncmp(outfile1, "mem:", 4) )  {


       strcpy(urltype, "ftpmem://");
       return 0;
    }

    if (!ftp_open_network(infile,&ftpfile,&command,&sock)) {
      fclose(ftpfile);
      fclose(command);

      if (strstr(infile,".gz") || (strstr(infile,".Z"))) {

	if (strstr(outfile1,".gz") || (strstr(outfile1,".Z"))) {
	  strcpy(urltype,"ftpcompress://");
	} else {
	  strcpy(urltype,"ftpfile://");
	}
      } else {
	strcpy(urltype,"ftpfile://");
      }
      return 0;
    }


    strcpy(newinfile,infile);
    strcat(newinfile,".gz");
    if (!ftp_open_network(newinfile,&ftpfile,&command,&sock)) {
      fclose(ftpfile);
      fclose(command);
      strcpy(infile,newinfile);

      if (strstr(outfile1,".gz") || (strstr(outfile1,".Z"))) {
	strcpy(urltype,"ftpcompress://");
      } else {
	strcpy(urltype,"ftpfile://");
      }
      return 0;
    }


    strcpy(newinfile,infile);
    strcat(newinfile,".Z");
    if (!ftp_open_network(newinfile,&ftpfile,&command,&sock)) {
      fclose(ftpfile);
      fclose(command);
      strcpy(infile,newinfile);
      if (strstr(outfile1,".gz") || (strstr(outfile1,".Z"))) {
	strcpy(urltype,"ftpcompress://");
      } else {
	strcpy(urltype,"ftpfile://");
      }
      return 0;
    }

  }
  return 0;
}
