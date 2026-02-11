process_tag(const char *str, struct xml_handle *handle_p)
{
  int len, i, p;

  if(handle_p==NULL)  return(1);

  len = strlen(str);
  if(!len)  return(1);

  if((str[0]==' ')||(str[0]=='>'))  return(1);

  for(i=0; i<len; i++)
  {
    if((str[i]==' ')||(str[i]=='>'))  break;
  }

  if(handle_p->elementname != NULL)  free(handle_p->elementname);

  handle_p->elementname = (char *)calloc(1, i + 1);
  if(handle_p->elementname==NULL)  return(1);
  strncpy(handle_p->elementname, str, i);
  handle_p->elementname[i] = 0;

  if(handle_p->attributes != NULL)  free(handle_p->attributes);

  if(str[i]!=' ')  return(0);

  i++;

  p = i;

  for(; i<len; i++)
  {
    if(str[i]=='>')  break;
  }

  len = i - p;

  if(len < 2)  return(0);

  handle_p->attributes = (char *)calloc(1, len + 1);
  if(handle_p->attributes==NULL)  return(1);
  strncpy(handle_p->attributes, str + p, len);
  handle_p->attributes[len] = 0;

  return(0);
}
