convert_to_number(int *value, const char *string)
{
  long int temp;
  char *tail;


  errno = 0;
  temp = strtol(string, &tail, 10);
  if (tail[0] != '\0')
  {
    fprintf(stderr, "convert_to_number: string is not a number\n");
    return 1;
  }
  if (errno != 0)
  {
    fprintf(stderr, "convert_to_number: number overflowed\n");
    return 1;
  }
  if ((temp <= INT_MIN) || (temp >= INT_MAX))
  {
    fprintf(stderr, "convert_to_number: too big or small integer\n");
    return 1;
  }
  *value = (int) temp;

  return 0;
}
