ReadAbaqusField(FILE *in,char *buffer,int *argtype,int *argno)


{
  int i,val,digits;
  static int maxargno=0,mode=0;

  val = fgetc(in);

  if(val==EOF) return(-1);
  if(val=='\n') val = fgetc(in);

  if(val=='*') {
    if(0) printf("start field\n");
    if((*argno) != maxargno)
      printf("The previous field was of wrong length, debugging time!\n");
    (*argno) = 0;
    mode = 0;
    val = fgetc(in);
    if(val=='\n') val = fgetc(in);
  }

  if(val=='I') {
    for(i=0;i<2;i++) {
      val = fgetc(in);
      if(val=='\n') val = fgetc(in);
      buffer[i] = val;
    }
    buffer[2] = '\0';
    digits = atoi(buffer);
    for(i=0;i<digits;i++) {
      val = fgetc(in);
      if(val=='\n') val = fgetc(in);
      buffer[i] = val;
    }
    buffer[digits] = '\0';
    (*argno)++;
    (*argtype) = 1;
    if((*argno) == 1) maxargno = atoi(buffer);
    if((*argno) == 2) mode = atoi(buffer);
  }
  else if(val=='D') {
    for(i=0;i<22;i++) {
      val = fgetc(in);
      if(val=='\n') val = fgetc(in);
      if(val=='D') val = 'E';
      buffer[i] = val;
    }
    buffer[22] = '\0';
    (*argno)++;
    (*argtype) = 2;
  }
  else if(val=='A') {
    for(i=0;i<8;i++) {
      val = fgetc(in);
      if(val=='\n') val = fgetc(in);
      buffer[i] = val;
    }
    buffer[8] = '\0';
    (*argno)++;
    (*argtype) = 3;
  }
  else {
    buffer[0] = val;
    buffer[1] = '\0';
    (*argtype) = 0;
  }
  return(mode);
}
