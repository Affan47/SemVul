is_vlan_iface(char *if_name)
{
   int fd,rc;
   struct vlan_ioctl_args vlan_args;

   fd = socket(PF_INET, SOCK_DGRAM, 0);


   if ( fd < 0 ) {
      return 0;
   };

   vlan_args.cmd = GET_VLAN_VID_CMD;
   strncpy(vlan_args.device1, if_name, sizeof(vlan_args.device1));
   rc = ioctl(fd,SIOCGIFVLAN,&vlan_args);

   close(fd);
   if (rc < 0) {
      return 0;
   } else {
      return 1;
   }

}
