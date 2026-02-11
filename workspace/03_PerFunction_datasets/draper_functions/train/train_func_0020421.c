_GD_FixEndianness(char* databuffer, size_t size, size_t ns)
{
  size_t i, j;
  char b;

  dtrace("%p, %zu, %zu", databuffer, size, ns);

  if (size == 1) {
    dreturnvoid();
    return;
  }

  for (i = 0; i < ns; ++i)
    for (j = 0; j < size / 2; ++j) {
      b = databuffer[size * (i + 1) - j - 1];
      databuffer[size * (i + 1) - j - 1] = databuffer[size * i + j];
      databuffer[size * i + j] = b;
    }

  dreturnvoid();
}
