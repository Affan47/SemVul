ping_timestamp (char *hostname)
{
  ping_set_type (ping, ICMP_TIMESTAMP);
  ping_set_event_handler (ping, recv_timestamp, NULL);
  ping_set_packetsize (ping, ICMP_TSLEN);

  if (ping_set_dest (ping, hostname))
    error (EXIT_FAILURE, 0, "unknown host");

  printf ("PING %s (%s): sending timestamp requests\n",
	  ping->ping_hostname, inet_ntoa (ping->ping_dest.ping_sockaddr.sin_addr));

  return ping_run (ping, timestamp_finish);
}
