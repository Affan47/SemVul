Compute_Hexa(char *str, char *hexa)
{
  *hexa++ = 'X';

  while (*str)
    {
      sprintf(hexa, "%02X", (unsigned) (unsigned char) *str);
      str++;
      hexa += 2;
    }

  *hexa = '\0';
  return hexa;
}
