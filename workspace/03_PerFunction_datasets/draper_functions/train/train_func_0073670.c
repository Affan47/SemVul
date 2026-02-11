osi_setup(struct pcmcia_device *link, u_short manfid, u_short cardid)
{
    struct net_device *dev = link->priv;
    int rc;


    if (pcmcia_loop_tuple(link, 0x90, pcmcia_osi_mac, dev))
	    return -1;

    if (((manfid == MANFID_OSITECH) &&
	 (cardid == PRODID_OSITECH_SEVEN)) ||
	((manfid == MANFID_PSION) &&
	 (cardid == PRODID_PSION_NET100))) {
	rc = osi_load_firmware(link);
	if (rc)
		return rc;
    } else if (manfid == MANFID_OSITECH) {

	set_bits(0x300, link->resource[0]->start + OSITECH_AUI_PWR);

	set_bits(0x300, link->resource[0]->start + OSITECH_RESET_ISR);
	dev_dbg(&link->dev, "AUI/PWR: %4.4x RESET/ISR: %4.4x\n",
	      inw(link->resource[0]->start + OSITECH_AUI_PWR),
	      inw(link->resource[0]->start + OSITECH_RESET_ISR));
    }
    return 0;
}
