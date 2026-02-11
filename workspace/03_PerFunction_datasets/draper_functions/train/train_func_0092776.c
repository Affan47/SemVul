stp_array_create_copy(const stp_array_t *array)
{
  stp_array_t *ret;
  CHECK_ARRAY(array);
  ret = stp_array_create(0, 0);
  stp_array_copy(ret, array);
  return ret;
}
