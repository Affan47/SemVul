read_page_fragment(Bit32u read_virtual_page, Bit32u read_page_offset, size_t read_size, void * buf)
{
  if (read_virtual_page != position_virtual_page)
  {
    set_virtual_page(read_virtual_page);
  }

  position_page_offset = read_page_offset;

  if (position_physical_page == SPARSE_PAGE_NOT_ALLOCATED)
  {
    if (parent_image != NULL)
    {
      return parent_image->read_page_fragment(read_virtual_page, read_page_offset, read_size, buf);
    }
    else
    {
      memset(buf, 0, read_size);
    }
  }
  else
  {
    Bit64s physical_offset = get_physical_offset();

    if (physical_offset != underlying_current_filepos)
    {
      off_t ret = ::lseek(fd, (off_t)physical_offset, SEEK_SET);

      if (ret == -1)
        panic(strerror(errno));
    }


    ssize_t readret = ::read(fd, buf, read_size);

    if (readret == -1)
    {
      panic(strerror(errno));
    }

    if ((size_t)readret != read_size)
    {
      panic("could not read block contents from file");
    }

    underlying_current_filepos = physical_offset + read_size;
  }

  return read_size;
}
