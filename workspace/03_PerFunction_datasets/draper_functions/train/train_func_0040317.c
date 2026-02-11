he_digit(int key)
{
  if (isdigit(key)) return key - '0';
  key = tolower(key);
  if (key >= 'a' && key <= 'f') return key - 'a' + 10;
  return -1;
}
