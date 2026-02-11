format_length(const String *format)
{
  uint size=0;
  const char *ptr=format->ptr();
  const char *end=ptr+format->length();

  for (; ptr != end ; ptr++)
  {
    if (*ptr != '%' || ptr == end-1)
      size++;
    else
    {
      switch(*++ptr) {
      case 'M':
      case 'W':
	size += 64;
	break;
      case 'D':
      case 'Y':
      case 'x':
      case 'X':
	size += 4;
	break;
      case 'a':
      case 'b':
	size += 32;
	break;
      case 'j':
	size += 3;
	break;
      case 'U':
      case 'u':
      case 'V':
      case 'v':
      case 'y':
      case 'm':
      case 'd':
      case 'h':
      case 'I':
      case 'i':
      case 'l':
      case 'p':
      case 'S':
      case 's':
      case 'c':
      case 'e':
	size += 2;
	break;
      case 'k':
      case 'H':
	size += 7;
	break;
      case 'r':
	size += 11;
	break;
      case 'T':
	size += 8;
	break;
      case 'f':
	size += 6;
	break;
      case 'w':
      case '%':
      default:
	size++;
	break;
      }
    }
  }
  return size;
}
