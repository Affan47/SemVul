link_open(const char *device) {
   link_t *handle;

   handle = Malloc(sizeof(*handle));
   memset(handle, '\0', sizeof(*handle));
   if ((handle->fd = socket(PF_PACKET, SOCK_RAW, 0)) < 0) {
      free(handle);
      return NULL;
   }
   strlcpy(handle->ifr.ifr_name, device, sizeof(handle->ifr.ifr_name));
   if ((ioctl(handle->fd, SIOCGIFINDEX, &(handle->ifr))) != 0)
      err_sys("ioctl");
   handle->sll.sll_family = PF_PACKET;
   handle->sll.sll_ifindex = handle->ifr.ifr_ifindex;
   handle->sll.sll_halen = ETH_ALEN;

   return handle;
}
