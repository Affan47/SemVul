__ifreq (struct ifreq **ifreqs, int *num_ifs, int sockfd)
{
  int fd = sockfd;
  struct ifconf ifc;
  int rq_len;
  int nifs;
# define RQ_IFS	4

  if (fd < 0)
    fd = __opensock ();
  if (fd < 0)
    {
      *num_ifs = 0;
      *ifreqs = NULL;
      return;
    }

  ifc.ifc_buf = NULL;


  ifc.ifc_buf = NULL;
  ifc.ifc_len = 0;
  if (__ioctl (fd, SIOCGIFCONF, &ifc) < 0 || ifc.ifc_len == 0)
    rq_len = RQ_IFS * sizeof (struct ifreq);
  else
    rq_len = ifc.ifc_len;


  ifc.ifc_len = rq_len;
  void *newp = realloc (ifc.ifc_buf, ifc.ifc_len);
  if (newp == NULL
      || (ifc.ifc_buf = newp, __ioctl (fd, SIOCGIFCONF, &ifc)) < 0)
    {
      free (ifc.ifc_buf);

      if (fd != sockfd)
	__close (fd);

      *num_ifs = 0;
      *ifreqs = NULL;
      return;
    }

  nifs = ifc.ifc_len / sizeof (struct ifreq);

  if (fd != sockfd)
    __close (fd);

  *num_ifs = nifs;
  *ifreqs = realloc (ifc.ifc_buf, nifs * sizeof (struct ifreq));
}
