extract_xml_field(char * line, char * result)
{
  int i,ctr=0;

  result[0]=0;


  for (i=0;i<strlen(line);i++) {
    if (line[i]=='>') break;
  }
  i++;

  while (i<strlen(line)-1) {
    if ((line[i]=='<') && (line[i+1]=='/')) break;
    result[ctr++] = line[i];
    i++;
  }
  result[ctr]=0;
  trim(result);
}
