tp_alloc(size_t n)
{

  if (n % BYTES_POINTER != 0) {
    n += (BYTES_POINTER - (n % BYTES_POINTER));
  }
  return palloc(n);
}
