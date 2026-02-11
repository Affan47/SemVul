GetPromisedIfStatus(int sk,char *vifdev,char *vaddress,char *vnetmask,char *vbroadcast)

{ struct sockaddr_in *sin;
  struct sockaddr_in netmask;
  int insane = false;
  struct hostent *hp;
  struct in_addr inaddr;
  char vbuff[CF_BUFSIZE];

CfOut(cf_verbose,""," -> Checking interface promises on %s\n",vifdev);

if ((hp = gethostbyname(VSYSNAME.nodename)) == NULL)
   {
   CfOut(cf_error,"gethostbyname","Error looking up host");
   return false;
   }
else
   {
   memcpy(&inaddr,hp->h_addr,hp->h_length);
   CfOut(cf_verbose,""," -> Address reported by nameserver: %s\n",inet_ntoa(inaddr));
   }

strcpy(IFR.ifr_name,vifdev);

if (ioctl(sk,SIOCGIFADDR, (caddr_t) &IFR) == -1)
   {
   return false;
   }

sin = (struct sockaddr_in *) &IFR.ifr_addr;

if (strlen(vaddress) > 0)
   {
   if (strcmp(vaddress,(char *)inet_ntoa(sin->sin_addr)) != 0)
      {
      CfOut(cf_error,"","Interface %s is configured with an address which differs from that promised\n",vifdev);
      insane = true;
      }
   }

if (strcmp((char *)inet_ntoa(*(struct in_addr *)(hp->h_addr)),(char *)inet_ntoa(sin->sin_addr)) != 0)
   {
   CfOut(cf_error,"","Interface %s is configured with an address which differs from that promised\n",vifdev);
   insane = true;
   }

if (ioctl(sk,SIOCGIFNETMASK, (caddr_t) &IFR) == -1)
   {
   return false;
   }

netmask.sin_addr = ((struct sockaddr_in *) &IFR.ifr_addr)->sin_addr;

CfOut(cf_verbose,""," -> Found netmask: %s\n",inet_ntoa(netmask.sin_addr));

strcpy(vbuff,inet_ntoa(netmask.sin_addr));

if (strcmp(vbuff,vnetmask))
   {
   CfOut(cf_error,"","Interface %s is configured with a netmask which differs from that promised\n",vifdev);
   insane = true;
   }

if (ioctl(sk,SIOCGIFBRDADDR, (caddr_t) &IFR) == -1)
   {
   return false;
   }

sin = (struct sockaddr_in *) &IFR.ifr_addr;
strcpy(vbuff,inet_ntoa(sin->sin_addr));

CfOut(cf_verbose,""," -> Found broadcast address: %s\n",inet_ntoa(sin->sin_addr));

GetDefaultBroadcastAddr(inet_ntoa(inaddr),vifdev,vnetmask,vbroadcast);

if (strcmp(vbuff,VNUMBROADCAST) != 0)
   {
   CfOut(cf_error,"","Interface %s is configured with a broadcast address which differs from that promised\n",vifdev);
   insane = true;
   }

return(insane);
}
