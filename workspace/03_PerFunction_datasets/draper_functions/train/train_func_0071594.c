reset_called_ptr(char* passed_pos)
{
  assert(unique_ptr);
  if (unique_ptr == NULL)
  {
    abort();
  }

  assert(&passed_pos == unique_ptr);
  if (&passed_pos != unique_ptr)
  {
    abort();
  }

  reset_called();
  unique_ptr= NULL;
}
