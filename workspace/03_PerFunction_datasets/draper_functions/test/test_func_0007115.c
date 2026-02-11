highbank_cphy_override_lane(u8 sata_port)
{
	u8 lane = port_data[sata_port].lane_mapping;
	u32 tmp, k = 0;

	if (unlikely(port_data[sata_port].phy_base == NULL))
		return;
	do {
		tmp = combo_phy_read(sata_port, CPHY_RX_INPUT_STS +
						lane * SPHY_LANE);
	} while ((tmp & SPHY_HALF_RATE) && (k++ < 1000));
	cphy_override_rx_mode(sata_port, 3);
	cphy_override_tx_attenuation(sata_port, port_data[sata_port].tx_atten);
}
