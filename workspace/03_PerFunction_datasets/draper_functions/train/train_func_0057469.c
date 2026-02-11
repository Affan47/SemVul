skip_nested_declarator (const char *&str) {
  int brackets = 1;
  str++;
  while (*str) {
    if (*str == '(')
      brackets++;
    else if (*str == ')')
      brackets--;
    str++;
    if (brackets == 0)
      return true;
  }
  return false;
}
