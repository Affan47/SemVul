get_arg(char* string) {
  char* cp=strchr(string,' ');
  if(cp==NULL) return NULL;
  for(;(*cp) == ' ';cp++);
  if(((*cp) == '\r') || ((*cp) == '\n') || ((*cp) == 0)) return NULL;
  char* np = cp+strcspn(cp,"\r\n");
  (*np)=0;
  return cp;
}
