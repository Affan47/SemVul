cgi_cso_field(linebuf, fieldname, valuebuf, buflen)
     char *linebuf, *fieldname, *valuebuf;
     int buflen;
{
  char *ptr;

  ptr=strchr(linebuf, ':');
  if (!ptr) return(0);


  if (strncmp(fieldname, ptr-strlen(fieldname), strlen(fieldname)))
    return(0);


  strncpy(valuebuf, ptr+2, buflen);
  return(1);
}
