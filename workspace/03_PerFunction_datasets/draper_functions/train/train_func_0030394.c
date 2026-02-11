offline_event_loop(void) {

  if (!daemon_mode)
    SAYF("[+] Processing capture data.\n\n");

  while (!stop_soon)  {

    if (pcap_dispatch(pt, -1, (pcap_handler)parse_packet, 0) <= 0) return;

  }

  WARN("User-initiated shutdown.");

}
