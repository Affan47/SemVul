init_address (char *remote, char *pcap_dev)
{

  struct hostent *h;

  local_address.s_addr = lft_getifaddr (pcap_dev);

  h = gethostbyname (remote);
  if (!h) {
    fprintf (stderr, "Unknown host: %s\n", remote);
    exit (1);
  }
  remote_address = *(struct in_addr *) h->h_addr;
  if (noisy && !nostatus) {
    print_host (local_address);
    printf (":%d", sport);
  }
  if (!nostatus)
    printf ("\n");
}
