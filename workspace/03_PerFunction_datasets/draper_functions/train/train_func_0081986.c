init_coq_global_data(long requested_size)
{
  int i;
  coq_global_data = alloc_shr(requested_size, 0);
  for (i = 0; i < requested_size; i++)
    Field (coq_global_data, i) = Val_unit;
}
