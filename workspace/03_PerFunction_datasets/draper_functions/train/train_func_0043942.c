cheating(void)
{

  if (option_pointer == NULL)
  {
    fprintf(stderr, "cheating: option_pointer is NULL\n");
    return 0;
  }

  if (option_pointer->free_select != 0)
    return 1;
  if (option_pointer->slow != 0)
    return 1;

  return 0;
}
