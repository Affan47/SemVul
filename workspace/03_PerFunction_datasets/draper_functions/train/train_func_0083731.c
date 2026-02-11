romannumeral(int n)
{
  static char buf[30];
  int len = 0;

  while (n >= 1000) {buf[len++] = 'M'; n -= 1000;}
  if (n >= 500) {buf[len++] = 'D'; n -= 500;}
  while (n >= 100) {buf[len++] = 'C'; n -= 100;}
  if (n >= 50) {buf[len++] = 'L'; n -= 50;}
  while (n >= 10) {buf[len++] = 'X'; n -= 10;}
  if (n >= 9) {buf[len++] = 'I'; buf[len++] = 'X'; n -= 9;}
  if (n >= 5) {buf[len++] = 'V'; n -= 5;}
  if (n >= 4) {buf[len++] = 'I'; buf[len++] = 'V'; n -= 4;}
  while (n >= 1) {buf[len++] = 'I'; n -= 1;}
  buf[len] = '\0';
  return buf;
}
