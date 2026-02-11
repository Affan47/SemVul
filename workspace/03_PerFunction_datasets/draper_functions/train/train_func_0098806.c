varySplit(char *line) {
  char floatString[50];
  int i = -1;
  int j = 0;

  splitline = parse_split(line);

  while(splitline[++i] != NULL) {
    for(j = 0; j < nvars; j++) {
      if(!strcmp(splitline[i],vnames[j])) {
	sprintf(floatString, "%f", vvals[j]);
	int length = strlen(splitline[i]);
	strncpy(splitline[i],floatString, length);
	break;
      }
    }
  }
}
