memory_bseek (bfd *abfd, file_ptr position, int direction)
{
  file_ptr nwhere;
  struct bfd_in_memory *bim;

  bim = (struct bfd_in_memory *) abfd->iostream;

  if (direction == SEEK_SET)
    nwhere = position;
  else
    nwhere = abfd->where + position;

  if (nwhere < 0)
    {
      abfd->where = 0;
      errno = EINVAL;
      return -1;
    }

  if ((bfd_size_type)nwhere > bim->size)
    {
      if (abfd->direction == write_direction
          || abfd->direction == both_direction)
        {
          bfd_size_type newsize, oldsize;

          oldsize = (bim->size + 127) & ~(bfd_size_type) 127;
          bim->size = nwhere;

          newsize = (bim->size + 127) & ~(bfd_size_type) 127;
          if (newsize > oldsize)
            {
              bim->buffer = (bfd_byte *) bfd_realloc_or_free (bim->buffer, newsize);
              if (bim->buffer == NULL)
                {
                  errno = EINVAL;
                  bim->size = 0;
                  return -1;
                }
              memset (bim->buffer + oldsize, 0, newsize - oldsize);
            }
        }
      else
        {
          abfd->where = bim->size;
          errno = EINVAL;
          bfd_set_error (bfd_error_file_truncated);
          return -1;
        }
    }
  return 0;
}
