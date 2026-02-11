set_mtu (int sfd, struct ifreq *ifr, int mtu)
{
#ifndef SIOCSIFMTU
  error (0, 0,
         "don't know how to set the interface mtu on this system");
  return -1;
#else
  int err = 0;

  ifr->ifr_mtu = mtu;
  err = ioctl (sfd, SIOCSIFMTU, ifr);
  if (err < 0)
    {
      error (0, errno, "SIOCSIFMTU failed");
      return -1;
    }
  if (verbose)
    printf ("Set mtu value of `%s' to `%i'.\n", ifr->ifr_name, ifr->ifr_mtu);
  return 0;
#endif
}
