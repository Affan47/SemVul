count_leading_zeros(const char *number)
{
  int idx;
  unsigned char count = 0;
  for (idx = 0; number[idx] == '0'; idx++) {
    count++;
  }
  if (count != 0 && number[idx] == '\0')
    count--;
  return count;
}
