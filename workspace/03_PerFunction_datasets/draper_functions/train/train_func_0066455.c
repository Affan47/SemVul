AllocateImageBuffer (PKV_DEV dev)
{
  int *size = dev->bytes_to_read;
  int sides = IS_DUPLEX (dev) ? 2 : 1;
  int i;
  size[0] = dev->params[0].bytes_per_line * dev->params[0].lines;
  size[1] = dev->params[1].bytes_per_line * dev->params[1].lines;

  DBG (DBG_proc, "AllocateImageBuffer: enter\n");

  for (i = 0; i < sides; i++)
    {
      SANE_Byte *p;
      DBG (DBG_proc, "AllocateImageBuffer: size(%c)=%d\n",
	   i ? 'B' : 'F', size[i]);

      if (dev->img_buffers[i] == NULL)
	{
	  p = (SANE_Byte *) malloc (size[i]);
	  if (p == NULL)
	    {
	      return SANE_STATUS_NO_MEM;
	    }
	  dev->img_buffers[i] = p;
	}
      else
	{
	  p = (SANE_Byte *) realloc (dev->img_buffers[i], size[i]);
	  if (p == NULL)
	    {
	      return SANE_STATUS_NO_MEM;
	    }
	  else
	    {
	      dev->img_buffers[i] = p;
	    }
	}
    }
  DBG (DBG_proc, "AllocateImageBuffer: exit\n");

  return SANE_STATUS_GOOD;
}
