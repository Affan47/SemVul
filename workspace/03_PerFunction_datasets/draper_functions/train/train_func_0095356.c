ReadImageData (PKV_DEV dev, int page)
{
  SANE_Status status;
  DBG (DBG_proc, "Reading image data for page %d\n", page);

  if (IS_DUPLEX (dev))
    {
      DBG (DBG_proc, "ReadImageData: Duplex %d\n", page);
      status = ReadImageDataDuplex (dev, page);
    }
  else
    {
      DBG (DBG_proc, "ReadImageData: Simplex %d\n", page);
      status = ReadImageDataSimplex (dev, page);
    }
  dev->img_pt[0] = dev->img_buffers[0];
  dev->img_pt[1] = dev->img_buffers[1];

  DBG (DBG_proc, "Reading image data for page %d, finished\n", page);

  return status;
}
