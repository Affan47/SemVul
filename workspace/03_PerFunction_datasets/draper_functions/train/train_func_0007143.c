print_line(decode_state_t *s)
{
  if (s->last != 0)
    if (s->last != (s->addr - s->len - 5))
      fprintf(stderr, "decode error, address calculation error\n");

  if (_verbose > 1)
    printf("[%04xh-%04xh] : %5d %s\n",
	   s->addr - s->len - 5,
	   s->addr - 1,
	   s->lineno,
	   s->text);
  else
    printf("%5d %s\n",
	   s->lineno,
	   s->text);

  s->last = s->addr;
}
