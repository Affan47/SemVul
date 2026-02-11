kv_free (KV_DEV ** pdev)
{
  KV_DEV *dev;

  dev = *pdev;

  if (dev == NULL)
    return;

  DBG (DBG_proc, "kv_free : enter\n");

  kv_close (dev);

  DBG (DBG_proc, "kv_free : free image buffer 0 \n");
  if (dev->img_buffers[0])
    free (dev->img_buffers[0]);
  DBG (DBG_proc, "kv_free : free image buffer 1 \n");
  if (dev->img_buffers[1])
    free (dev->img_buffers[1]);
  DBG (DBG_proc, "kv_free : free scsi device name\n");
  if (dev->scsi_device_name)
    free (dev->scsi_device_name);

  DBG (DBG_proc, "kv_free : free SCSI buffer\n");
  if (dev->buffer0)
    free (dev->buffer0);

  DBG (DBG_proc, "kv_free : free dev \n");
  free (dev);

  *pdev = NULL;

  DBG (DBG_proc, "kv_free : exit\n");
}
