rt61pci_config_ps(struct rt2x00_dev *rt2x00dev,
				struct rt2x00lib_conf *libconf)
{
	enum dev_state state =
	    (libconf->conf->flags & IEEE80211_CONF_PS) ?
		STATE_SLEEP : STATE_AWAKE;
	u32 reg;

	if (state == STATE_SLEEP) {
		rt2x00mmio_register_read(rt2x00dev, MAC_CSR11, &reg);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN,
				   rt2x00dev->beacon_int - 10);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP,
				   libconf->conf->listen_interval - 1);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 5);


		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00mmio_register_write(rt2x00dev, MAC_CSR11, reg);

		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 1);
		rt2x00mmio_register_write(rt2x00dev, MAC_CSR11, reg);

		rt2x00mmio_register_write(rt2x00dev, SOFT_RESET_CSR,
					  0x00000005);
		rt2x00mmio_register_write(rt2x00dev, IO_CNTL_CSR, 0x0000001c);
		rt2x00mmio_register_write(rt2x00dev, PCI_USEC_CSR, 0x00000060);

		rt61pci_mcu_request(rt2x00dev, MCU_SLEEP, 0xff, 0, 0);
	} else {
		rt2x00mmio_register_read(rt2x00dev, MAC_CSR11, &reg);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 0);
		rt2x00mmio_register_write(rt2x00dev, MAC_CSR11, reg);

		rt2x00mmio_register_write(rt2x00dev, SOFT_RESET_CSR,
					  0x00000007);
		rt2x00mmio_register_write(rt2x00dev, IO_CNTL_CSR, 0x00000018);
		rt2x00mmio_register_write(rt2x00dev, PCI_USEC_CSR, 0x00000020);

		rt61pci_mcu_request(rt2x00dev, MCU_WAKEUP, 0xff, 0, 0);
	}
}
