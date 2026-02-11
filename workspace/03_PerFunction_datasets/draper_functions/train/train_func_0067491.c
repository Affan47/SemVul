dio_input_skip(struct data_in *din, size_t size)
{
  if (enough_data(din, size)) {
    din->current += size;
    return TRUE;
  } else {
    return FALSE;
  }
}
