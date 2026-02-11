net_receive_packet(unsigned char *buffer, int len)
{
	struct net_packet_info *np;
	struct packet_info p;

	if (len < sizeof(struct net_packet_info))
		return 0;

	np = (struct net_packet_info *)buffer;

	if (np->phy_rate == 0)
		return 0;

	if (np->version != PKT_INFO_VERSION)
		return 0;

	memset(&p, 0, sizeof(p));
	p.pkt_types	= le32toh(np->pkt_types);
	p.phy_signal	= le32toh(np->phy_signal);
	p.phy_noise	= le32toh(np->phy_noise);
	p.phy_snr	= le32toh(np->phy_snr);
	p.phy_rate	= le32toh(np->phy_rate);
	p.phy_freq	= le32toh(np->phy_freq);
	p.phy_chan	= np->phy_chan;
	p.phy_flags	= le32toh(np->phy_flags);
	p.wlan_len	= le32toh(np->wlan_len);
	p.wlan_type	= le32toh(np->wlan_type);
	memcpy(p.wlan_src, np->wlan_src, MAC_LEN);
	memcpy(p.wlan_dst, np->wlan_dst, MAC_LEN);
	memcpy(p.wlan_bssid, np->wlan_bssid, MAC_LEN);
	memcpy(p.wlan_essid, np->wlan_essid, MAX_ESSID_LEN);
	p.wlan_tsf	= le64toh(np->wlan_tsf);
	p.wlan_bintval	= le32toh(np->wlan_bintval);
	p.wlan_mode	= le32toh(np->wlan_mode);
	p.wlan_channel = np->wlan_channel;
	p.wlan_qos_class = np->wlan_qos_class;
	p.wlan_nav	= le32toh(np->wlan_nav);
	p.wlan_seqno	= le32toh(np->wlan_seqno);
	np->wlan_flags	= le32toh(np->wlan_flags);
	if (np->wlan_flags & PKT_WLAN_FLAG_WEP)
		p.wlan_wep = 1;
	if (np->wlan_flags & PKT_WLAN_FLAG_RETRY)
		p.wlan_retry = 1;
	p.ip_src	= np->ip_src;
	p.ip_dst	= np->ip_dst;
	p.tcpudp_port	= le32toh(np->tcpudp_port);
	p.olsr_type	= le32toh(np->olsr_type);
	p.olsr_neigh	= le32toh(np->olsr_neigh);
	p.olsr_tc	= le32toh(np->olsr_tc);

	handle_packet(&p);

	return sizeof(struct net_packet_info);
}
