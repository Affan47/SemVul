obstack_octal_grow (struct obstack *o, const char *str)
{
  int value = *str++ - '0';

  while (*str)
    value = 8 * value + *str++ - '0';
  obstack_1grow (o, value);
}
