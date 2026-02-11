libc_scanf_convert (char *fmt)
{
  char  *p = fmt;

  if (! option_libc_scanf)
    return 0;

  for ( ; *fmt != '\0'; fmt++)
    {
      switch (*fmt) {
      case 'F':
      case 'Q':
      case 'Z':

        *p++ = 'l';
        break;
      default:
        *p++ = *fmt;
        break;
      }
    }
  *p = '\0';
  return 1;
}
