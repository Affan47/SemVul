mii_get_basic (const char *ifname)
{
	int i, mii_val[32];
	int bmcr, bmsr, advert, lkpar;
	unsigned short autonegotiate = 0;
	mii_data_result data;
	int sock;

	memset (data.iface, 0, 100);
	memset (data.media, 0, 100);


	if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {
		data.has_data = 0;
		return data;
	}


	strncpy (ifr.ifr_name, ifname, IFNAMSIZ);
	if (ioctl (sock, SIOCGMIIPHY, &ifr) < 0) {
		if (errno != ENODEV) {
			data = mii_get_basic_wireless (sock, ifname);
			if (! data.has_data) {
				strcat (data.iface, ifname);
				strcat (data.media, "Unknown");
				data.state = 0;
			}
			return data;
		}
		data.has_data = 0;
		close (sock);
		return data;
	}
	data.has_data = 1;


	mdio_read (sock, MII_BMSR);
	for (i = 0; i < 8; i++)
		mii_val[i] = mdio_read (sock, i);

    if (mii_val[MII_BMCR] == 0xffff) {
	    data.has_data = 0;
		close (sock);
    	return data;
    }


	bmcr = mii_val[MII_BMCR];
	bmsr = mii_val[MII_BMSR];
	advert = mii_val[MII_ANAR];
	lkpar = mii_val[MII_ANLPAR];

	sprintf (data.iface, "%s", ifr.ifr_name);
	if (bmcr & MII_BMCR_AN_ENA) {
		if (bmsr & MII_BMSR_AN_COMPLETE) {
			if (advert & lkpar) {
				strcat (data.media, media_list (advert & lkpar, 1));
				autonegotiate = 1;
			}
		}
	}
	if (! autonegotiate) {
		sprintf (data.media, "%s Mbit %sD",
			 (bmcr & MII_BMCR_100MBIT) ? "100" : "10",
			 (bmcr & MII_BMCR_DUPLEX) ? "F" : "H");
	}
	data.state = (bmsr & MII_BMSR_LINK_VALID);

	close (sock);
	return data;
}
