modify_read_size (GVfsReadChannel *channel,
		  guint32 requested_size)
{
  guint32 real_size;

  if (channel->read_count <= 1)
    real_size = 4*1024;
  else if (channel->read_count <= 2)
    real_size = 8*1024;
  else if (channel->read_count <= 3)
    real_size = 16*1024;
  else if (channel->read_count <= 4)
    real_size = 32*1024;
  else
    real_size = 64*1024;

  if (requested_size > real_size)
      real_size = requested_size;


  if (real_size > 128 * 1024)
    real_size = 128 * 1024;

  return real_size;
}
