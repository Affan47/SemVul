parse_prism_header(unsigned char** buf, int len, struct packet_info* p)
{
	wlan_ng_prism2_header* ph;

	DEBUG("PRISM2 HEADER\n");

	if (len < sizeof(wlan_ng_prism2_header))
		return -1;

	ph = (wlan_ng_prism2_header*)*buf;


	if (((int)ph->noise.data) < 0) {

		p->phy_signal = ph->signal.data;
		p->phy_noise = ph->noise.data;
		p->phy_snr = ph->rssi.data;
	}
	else if (((int)ph->rssi.data) < 0) {

		p->phy_signal = ph->rssi.data;
		p->phy_noise = -95;
		p->phy_snr = 95 + ph->rssi.data;
	}
	else {

		p->phy_signal = ph->signal.data;
		p->phy_noise = ph->noise.data;
		p->phy_snr = ph->signal.data - ph->noise.data;
	}

	p->phy_rate = ph->rate.data;


	if (p->phy_snr < 0)
		p->phy_snr = -p->phy_snr;
	if (p->phy_snr > 99)
		p->phy_snr = 99;
	if (p->phy_rate == 0 || p->phy_rate > 108) {

		DEBUG("*** fixing wrong rate\n");
		if (ph->channel.data > 14)
			p->phy_rate = 12;
		else
			p->phy_rate = 2;
	}


	if (ph->channel.data > 14)
		p->phy_flags |= PHY_FLAG_A;
	else
		p->phy_flags |= PHY_FLAG_G;

	p->phy_flags |= PHY_FLAG_SHORTPRE;

	DEBUG("devname: %s\n", ph->devname);
	DEBUG("signal: %d -> %d\n", ph->signal.data, p->phy_signal);
	DEBUG("noise: %d -> %d\n", ph->noise.data, p->phy_noise);
	DEBUG("rate: %d\n", ph->rate.data);
	DEBUG("rssi: %d\n", ph->rssi.data);
	DEBUG("*** SNR %d\n", p->phy_snr);

	*buf = *buf + sizeof(wlan_ng_prism2_header);
	return len - sizeof(wlan_ng_prism2_header);
}
