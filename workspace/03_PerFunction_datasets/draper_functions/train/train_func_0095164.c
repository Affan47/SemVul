project_stack(char *name, int len)
{
  int size;

  name[len] = 0;
  size = atoi(name);

  if (size >= 1 && size <= 64)
    STACK_size = size * 1024L * sizeof(VALUE);
}
