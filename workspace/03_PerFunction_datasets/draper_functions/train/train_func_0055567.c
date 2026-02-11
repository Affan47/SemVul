tuntap_open(tuntap_dev *device,
                char *dev,
                const char *address_mode,
                char *device_ip,
                char *device_mask,
                const char * device_mac,
		int mtu) {
  char *tuntap_device = "/dev/net/tun";
#define N2N_LINUX_SYSTEMCMD_SIZE 128
  char buf[N2N_LINUX_SYSTEMCMD_SIZE];
  struct ifreq ifr;
  int rc;

  device->fd = open(tuntap_device, O_RDWR);
  if(device->fd < 0) {
    printf("ERROR: ioctl() [%s][%d]\n", strerror(errno), errno);
    return -1;
  }

  memset(&ifr, 0, sizeof(ifr));
  ifr.ifr_flags = IFF_TAP|IFF_NO_PI;
  strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  rc = ioctl(device->fd, TUNSETIFF, (void *)&ifr);

  if(rc < 0) {
    traceEvent(TRACE_ERROR, "ioctl() [%s][%d]\n", strerror(errno), rc);
    close(device->fd);
    return -1;
  }


  strncpy(device->dev_name, ifr.ifr_name, MIN(IFNAMSIZ, N2N_IFNAMSIZ) );

  if ( device_mac && device_mac[0] != '\0' )
  {

      snprintf(buf, sizeof(buf), "/sbin/ifconfig %s hw ether %s",
               ifr.ifr_name, device_mac );
      system(buf);
      traceEvent(TRACE_INFO, "Setting MAC: %s", buf);
  }

  if ( 0 == strncmp( "dhcp", address_mode, 5 ) )
  {
      snprintf(buf, sizeof(buf), "/sbin/ifconfig %s %s mtu %d up",
               ifr.ifr_name, device_ip, mtu);
  }
  else
  {
      snprintf(buf, sizeof(buf), "/sbin/ifconfig %s %s netmask %s mtu %d up",
               ifr.ifr_name, device_ip, device_mask, mtu);
  }

  system(buf);
  traceEvent(TRACE_INFO, "Bringing up: %s", buf);

  device->ip_addr = inet_addr(device_ip);
  device->device_mask = inet_addr(device_mask);
  read_mac(dev, device->mac_addr);
  return(device->fd);
}
