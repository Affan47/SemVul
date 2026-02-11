get_own_ip_addr(int iface_nmbr ){
  struct ifreq req;
  int fd;
  char * addr;
  uint32_t address;
  char name[6];
  sprintf(name, "lec%d", iface_nmbr );
  memcpy(req.ifr_ifrn.ifrn_name,name,sizeof(name));
  fd =  socket( AF_INET, SOCK_STREAM, IPPROTO_IP );
  if(fd < 0){
    printf("mpcd: get_vars.c: socket creation failed.\n");
    exit(1);
  }
  if(ioctl(fd,SIOCGIFADDR,&req)<0){
    printf("mpcd: get_vars.c: ioctl failed: %s\n", strerror(errno));
    exit(1);
  }
  addr = req.ifr_ifru.ifru_addr.sa_data;
  address = ((unsigned char)addr[2] << 24) |
            ((unsigned char)addr[3] << 16) |
            ((unsigned char)addr[4] << 8 ) |
             (unsigned char)addr[5] ;
  close(fd);
  return address;
}
