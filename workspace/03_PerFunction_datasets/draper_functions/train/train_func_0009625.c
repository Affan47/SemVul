ping_address (char *hostname)
{
  ping_set_type (ping, ICMP_ADDRESS);
  ping_set_event_handler (ping, recv_address, NULL);
  ping_set_packetsize (ping, ICMP_MASKLEN);
  ping_set_count (ping, 1);

  if (ping_set_dest (ping, hostname))
    error (EXIT_FAILURE, 0, "unknown host");

  printf ("PING %s (%s): sending address mask request\n",
	  ping->ping_hostname, inet_ntoa (ping->ping_dest.ping_sockaddr.sin_addr));

  return ping_run (ping, address_finish);
}
