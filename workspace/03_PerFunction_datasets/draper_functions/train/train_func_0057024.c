EPPbufferWrite (int size, unsigned char *source)
{
#ifdef HAVE_LINUX_PPDEV_H
  int fd, mode, rc;
  unsigned char bval;
#endif


#ifdef HAVE_LINUX_PPDEV_H

  fd = sanei_umax_pp_getparport ();
  if (fd > 0)
    {
      bval = 0xC0;
      mode = IEEE1284_MODE_EPP | IEEE1284_ADDR;
      rc = ioctl (fd, PPSETMODE, &mode);
      if (rc)
	DBG (0, "ppdev ioctl returned <%s>  (%s:%d)\n", strerror (errno),
	     __FILE__, __LINE__);
      rc = write (fd, &bval, 1);

      mode = IEEE1284_MODE_EPP | IEEE1284_DATA;
      rc = ioctl (fd, PPSETMODE, &mode);
      if (rc)
	DBG (0, "ppdev ioctl returned <%s>  (%s:%d)\n", strerror (errno),
	     __FILE__, __LINE__);
      rc = write (fd, source, size);
      return;
    }

#endif
  EPPBlockMode (0xC0);
  Outsb (EPPDATA, source, size);
}
