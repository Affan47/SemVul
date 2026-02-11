default_local_infile_end(void *ptr)
{
  default_local_infile_data *data= (default_local_infile_data *) ptr;
  if (data)
  {
    if (data->fd >= 0)
      my_close(data->fd, MYF(MY_WME));
    my_free(ptr);
  }
}
