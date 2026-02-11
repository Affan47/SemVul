htoi(const char *str)
{
  int		ret = 0;


  for (; isspace(*str); str++) {
  }


  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
  }

  for (; isdigit(*str) ||
       (*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F');
       str++) {
    ret *= 16;
    if (*str >= 'a' && *str <= 'f') {
      ret += *str - 'a' + 10;
    }
    else if (*str >= 'A' && *str <= 'F') {
      ret += *str - 'A' + 10;
    }
    else {
      ret += *str - '0';
    }
  }

  return ret;
}
