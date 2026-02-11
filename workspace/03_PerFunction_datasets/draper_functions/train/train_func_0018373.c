Getline(char *line1,FILE *io)
{
  int i,isend;
  char line0[MAXLINESIZE],*charend,*matcpntr,*matcpntr0;

  for(i=0;i<MAXLINESIZE;i++)
    line0[i] = ' ';

 newline:

  charend = fgets(line0,MAXLINESIZE,io);
  isend = (charend == NULL);

  if(isend) return(1);

  if(line0[0] == '#' || line0[0] == '%' || line0[0] == '!') goto newline;
  if(!matcactive && line0[0] == '*') goto newline;

#ifndef DISABLE_MATC
  if(matcactive) {
    matcpntr0 = strchr(line0,'$');
    if(matcpntr0) {
      matcpntr = mtc_domath(&matcpntr0[1]);
      if(matcpntr) {
	strcpy(matcpntr0, matcpntr);
	if(0) printf("A: %s\n%s\n",matcpntr0,matcpntr);
      }
    }
  }
#endif

  if(strstr(line0,"subcell boundaries")) goto newline;
  if(strstr(line0,"material structure")) goto newline;
  if(strstr(line0,"mode")) goto newline;
  if(strstr(line0,"type")) goto newline;

  for(i=0;i<MAXLINESIZE;i++)
    line1[i] = toupper(line0[i]);

  if(iodebug) {
    printf("line: ");
    for(i=0;i<40;i++) printf("%c",line1[i]);
    printf("\n");
  }

  return(0);
}
