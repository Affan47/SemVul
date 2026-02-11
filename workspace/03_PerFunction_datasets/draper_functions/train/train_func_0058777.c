c_isalnum (int c)
{
#if C_CTYPE_CONSECUTIVE_DIGITS \
    && C_CTYPE_CONSECUTIVE_UPPERCASE && C_CTYPE_CONSECUTIVE_LOWERCASE
#if C_CTYPE_ASCII
  return ((c >= '0' && c <= '9')
          || ((c & ~0x20) >= 'A' && (c & ~0x20) <= 'Z'));
#else
  return ((c >= '0' && c <= '9')
          || (c >= 'A' && c <= 'Z')
          || (c >= 'a' && c <= 'z'));
#endif
#else
  switch (c)
    {
    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
    case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
    case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
    case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
    case 'Y': case 'Z':
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
    case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
    case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
    case 's': case 't': case 'u': case 'v': case 'w': case 'x':
    case 'y': case 'z':
      return 1;
    default:
      return 0;
    }
#endif
}
