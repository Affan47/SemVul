rfbUsage(void)
{
    rfbProtocolExtension* extension;

    fprintf(stderr, "-rfbport port          TCP port for RFB protocol\n");
#ifdef LIBVNCSERVER_IPv6
    fprintf(stderr, "-rfbportv6 port        TCP6 port for RFB protocol\n");
#endif
    fprintf(stderr, "-rfbwait time          max time in ms to wait for RFB client\n");
    fprintf(stderr, "-rfbauth passwd-file   use authentication on RFB protocol\n"
                    "                       (use 'storepasswd' to create a password file)\n");
    fprintf(stderr, "-rfbversion 3.x        Set the version of the RFB we choose to advertise\n");
    fprintf(stderr, "-permitfiletransfer    permit file transfer support\n");
    fprintf(stderr, "-passwd plain-password use authentication \n"
                    "                       (use plain-password as password, USE AT YOUR RISK)\n");
    fprintf(stderr, "-deferupdate time      time in ms to defer updates "
                                                             "(default 40)\n");
    fprintf(stderr, "-deferptrupdate time   time in ms to defer pointer updates"
                                                           " (default none)\n");
    fprintf(stderr, "-desktop name          VNC desktop name (default \"LibVNCServer\")\n");
    fprintf(stderr, "-alwaysshared          always treat new clients as shared\n");
    fprintf(stderr, "-nevershared           never treat new clients as shared\n");
    fprintf(stderr, "-dontdisconnect        don't disconnect existing clients when a "
                                                             "new non-shared\n"
                    "                       connection comes in (refuse new connection "
                                                                "instead)\n");
    fprintf(stderr, "-httpdir dir-path      enable http server using dir-path home\n");
    fprintf(stderr, "-httpport portnum      use portnum for http connection\n");
#ifdef LIBVNCSERVER_IPv6
    fprintf(stderr, "-httpportv6 portnum    use portnum for IPv6 http connection\n");
#endif
    fprintf(stderr, "-enablehttpproxy       enable http proxy support\n");
    fprintf(stderr, "-progressive height    enable progressive updating for slow links\n");
    fprintf(stderr, "-listen ipaddr         listen for connections only on network interface with\n");
    fprintf(stderr, "                       addr ipaddr. '-listen localhost' and hostname work too.\n");
#ifdef LIBVNCSERVER_IPv6
    fprintf(stderr, "-listenv6 ipv6addr     listen for IPv6 connections only on network interface with\n");
    fprintf(stderr, "                       addr ipv6addr. '-listen localhost' and hostname work too.\n");
#endif

    for(extension=rfbGetExtensionIterator();extension;extension=extension->next)
	if(extension->usage)
		extension->usage();
    rfbReleaseExtensionIterator();
}
