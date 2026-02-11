print_prads_stats()
{
    extern uint64_t cxtrackerid;
    olog("-- prads:\n");
    olog("-- Total packets received from libpcap    :%12u\n",config.pr_s.got_packets);
    olog("-- Total Ethernet packets received        :%12u\n",config.pr_s.eth_recv);
    olog("-- Total VLAN packets received            :%12u\n",config.pr_s.vlan_recv);
    olog("-- Total ARP packets received             :%12u\n",config.pr_s.arp_recv);
    olog("-- Total IPv4 packets received            :%12u\n",config.pr_s.ip4_recv);
    olog("-- Total IPv6 packets received            :%12u\n",config.pr_s.ip6_recv);
    olog("-- Total Other link packets received      :%12u\n",config.pr_s.otherl_recv);
    olog("-- Total IPinIPv4 packets received        :%12u\n",config.pr_s.ip4ip_recv);
    olog("-- Total IPinIPv6 packets received        :%12u\n",config.pr_s.ip6ip_recv);
    olog("-- Total GRE packets received             :%12u\n",config.pr_s.gre_recv);
    olog("-- Total TCP packets received             :%12u\n",config.pr_s.tcp_recv);
    olog("-- Total UDP packets received             :%12u\n",config.pr_s.udp_recv);
    olog("-- Total ICMP packets received            :%12u\n",config.pr_s.icmp_recv);
    olog("-- Total Other transport packets received :%12u\n",config.pr_s.othert_recv);
    olog("--\n");
    olog("-- Total sessions tracked                 :%12lu\n", cxtrackerid);
    olog("-- Total assets detected                  :%12u\n",config.pr_s.assets);
    olog("-- Total TCP OS fingerprints detected     :%12u\n",config.pr_s.tcp_os_assets);
    olog("-- Total UDP OS fingerprints detected     :%12u\n",config.pr_s.udp_os_assets);
    olog("-- Total ICMP OS fingerprints detected    :%12u\n",config.pr_s.icmp_os_assets);
    olog("-- Total DHCP OS fingerprints detected    :%12u\n",config.pr_s.dhcp_os_assets);
    olog("-- Total TCP service assets detected      :%12u\n",config.pr_s.tcp_services);
    olog("-- Total TCP client assets detected       :%12u\n",config.pr_s.tcp_clients);
    olog("-- Total UDP service assets detected      :%12u\n",config.pr_s.udp_services);
    olog("-- Total UDP client assets detected       :%12u\n",config.pr_s.udp_clients);
}
