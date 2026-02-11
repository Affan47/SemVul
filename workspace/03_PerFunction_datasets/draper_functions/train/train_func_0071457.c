_my_b_write(register IO_CACHE *info, const uchar *Buffer, size_t Count)
{
  size_t rest_length,length;
  my_off_t pos_in_file= info->pos_in_file;

  DBUG_EXECUTE_IF("simulate_huge_load_data_file",
                  {
                    pos_in_file=(my_off_t)(5000000000ULL);
                  });
  if (pos_in_file+info->buffer_length > info->end_of_file)
  {
    my_errno=errno=EFBIG;
    return info->error = -1;
  }

  rest_length= (size_t) (info->write_end - info->write_pos);
  memcpy(info->write_pos,Buffer,(size_t) rest_length);
  Buffer+=rest_length;
  Count-=rest_length;
  info->write_pos+=rest_length;

  if (my_b_flush_io_cache(info,1))
    return 1;
  if (Count >= IO_SIZE)
  {
    length=Count & (size_t) ~(IO_SIZE-1);
    if (info->seek_not_done)
    {


      if (mysql_file_seek(info->file, info->pos_in_file, MY_SEEK_SET, MYF(0)))
      {
        info->error= -1;
        return (1);
      }
      info->seek_not_done=0;
    }
    if (mysql_file_write(info->file, Buffer, length, info->myflags | MY_NABP))
      return info->error= -1;


    if (info->share)
      copy_to_read_buffer(info, Buffer, length);

    Count-=length;
    Buffer+=length;
    info->pos_in_file+=length;
  }
  memcpy(info->write_pos,Buffer,(size_t) Count);
  info->write_pos+=Count;
  return 0;
}
