UUBrokenByNetscape (char *string)
{
  char *ptr;
  int len;

  if (string==NULL || (len=strlen(string))<3)
    return 0;

  if ((ptr = _FP_stristr (string, "<a href=")) != NULL) {
    if (_FP_stristr (string, "</a>") > ptr)
      return 2;
  }

  ptr = string + len;

  while (len && (*(ptr-1)=='\015' || *(ptr-1)=='\012')) {
    ptr--; len--;
  }
  if (len<3)         return 0;
  if (*--ptr == ' ') ptr--;
  ptr--;

  if (_FP_strnicmp (ptr, "<a", 2) == 0)
    return 1;

  return 0;
}
