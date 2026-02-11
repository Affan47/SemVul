__url_set_password(URL this, char *str)
{
  int i;
  char *a;
  char *s;
  a = strchr(str, '@');
  s = strchr(str, '/');

  if((!a) || (s && (a >= s)) ){
    return str;
  }


  for(i = 0 ; str[i] != '@'; i++);
  this->password = xmalloc(i+1);

  memcpy(this->password, str, i);
  this->password[i] = '\0';

  str += i + 1;

  return str;
}
