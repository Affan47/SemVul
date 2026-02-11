h5_rmprefix(const char *filename)
{
    const char *ret_ptr;

    if ((ret_ptr = HDstrstr(filename, ":")) == NULL)
  ret_ptr = filename;
    else
  ret_ptr++;

    return(ret_ptr);
}
