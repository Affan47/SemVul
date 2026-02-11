mailimap_nz_number_alloc_parse(mailstream * fd, MMAPString * buffer,
			       size_t * indx,
			       uint32_t ** result,
			       size_t progr_rate,
			       progress_function * progr_fun)
{
  uint32_t number;
  uint32_t * number_alloc;
  size_t cur_token;
  int r;

  cur_token = * indx;

  r = mailimap_nz_number_parse(fd, buffer, &cur_token, &number);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  number_alloc = mailimap_number_alloc_new(number);
  if (number_alloc == NULL)
    return MAILIMAP_ERROR_MEMORY;

  * indx = cur_token;
  * result = number_alloc;

  return MAILIMAP_NO_ERROR;
}
