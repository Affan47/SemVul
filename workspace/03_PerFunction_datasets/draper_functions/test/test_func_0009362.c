json_ConvertEscapeChar(char escape_char)
{
  char r = 0;
  switch(escape_char)
  {
    case 't':
      r = 9;
      break;
    case 'a':
      r = 7;
      break;
    case 'b':
      r = 8;
      break;
    case 'n':
      r = 10;
      break;
    case 'v':
      r = 11;
      break;
    case 'r':
      r = 13;
      break;
    case '"':
      r = 34;
      break;
    case '\'':
      r = 39;
      break;
    case '?':
      r = 63;
      break;
    case '\\':
      r = 92;
      break;
    default:
      r = 0;
  }
  return(r);
}
