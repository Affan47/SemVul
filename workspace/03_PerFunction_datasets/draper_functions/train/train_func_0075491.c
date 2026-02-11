getSpecialName(char *number) {
  int i,j,l;
  l=strlen(number);
  for (i=0; i<nService; i++)
    for(j=0; j<Service[i].nCode; j++)
      if(strmatch(Service[i].Codes[j], number)>=l)
        return Service[i].Name;
  return 0;
}
