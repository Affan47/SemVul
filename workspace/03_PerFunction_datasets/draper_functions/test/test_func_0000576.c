addchar(c)
inchr c;
{
  int smushamount,row,k,column;
  outchr *templine;

  getletter(c);
  smushamount = smushamt();
  if (outlinelen+currcharwidth-smushamount>outlinelenlimit
      ||inchrlinelen+1>inchrlinelenlimit) {
    return 0;
    }

  templine = (outchr*)myalloc(sizeof(outchr)*(outlinelenlimit+1));
  for (row=0;row<charheight;row++) {
    if (right2left) {
      STRCPY(templine,currchar[row]);
      for (k=0;k<smushamount;k++) {
        templine[currcharwidth-smushamount+k] =
          smushem(templine[currcharwidth-smushamount+k],outputline[row][k]);
        }
      STRCAT(templine,outputline[row]+smushamount);
      STRCPY(outputline[row],templine);
      }
    else {
      for (k=0;k<smushamount;k++) {
	column = outlinelen-smushamount+k;
	if (column < 0) {
	  column = 0;
	  }
        outputline[row][column] =
          smushem(outputline[row][column],currchar[row][k]);
        }
      STRCAT(outputline[row],currchar[row]+smushamount);
      }
    }
  free(templine);
  outlinelen = STRLEN(outputline[0]);
  inchrline[inchrlinelen++] = c;
  return 1;
}
