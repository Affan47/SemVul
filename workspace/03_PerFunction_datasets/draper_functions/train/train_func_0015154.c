__url_set_path(URL this, char *str)
{
  int  i;
  int  j;

  for(i = strlen(str); i > 0 && str[i] != '/'; i--);
  for(j = 0; str[j] && (str[j] != '#' && !isspace(str[j])); j++);


  if(str[i] != '/'){
    this->path    = xmalloc(2);
    this->request = xmalloc(2);
    strncpy(this->path,    "/", 2);
    strncpy(this->request, "/", 2);
    this->path[1]    = '\0';
    this->request[1] = '\0';
  } else {
    this->path    = xmalloc(i+2);
    this->request = xmalloc(j+2);
    memcpy(this->path, str, i+1);
    memcpy(this->request, str, j+1);
    this->path[i] = '/';
    this->path[i + 1]    = '\0';
    if (this->request[j]=='#') {
      this->request[j]   = '\0';
    } else {
      this->request[j+1] = '\0';
    }
  }

  str += i + 1;
  return str;
}
