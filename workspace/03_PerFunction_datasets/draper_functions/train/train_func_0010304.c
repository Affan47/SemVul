_pcre_was_newline(USPTR ptr, int type, USPTR startptr, int *lenptr, BOOL utf8)
{
int c;
ptr--;
#ifdef SUPPORT_UTF8
if (utf8)
  {
  BACKCHAR(ptr);
  GETCHAR(c, ptr);
  }
else c = *ptr;
#else
c = *ptr;
#endif

if (type == NLTYPE_ANYCRLF) switch(c)
  {
  case 0x000a: *lenptr = (ptr > startptr && ptr[-1] == 0x0d)? 2 : 1;
               return TRUE;
  case 0x000d: *lenptr = 1; return TRUE;
  default: return FALSE;
  }

else switch(c)
  {
  case 0x000a: *lenptr = (ptr > startptr && ptr[-1] == 0x0d)? 2 : 1;
               return TRUE;
  case 0x000b:
  case 0x000c:
  case 0x000d: *lenptr = 1; return TRUE;
  case 0x0085: *lenptr = utf8? 2 : 1; return TRUE;
  case 0x2028:
  case 0x2029: *lenptr = 3; return TRUE;
  default: return FALSE;
  }
}
