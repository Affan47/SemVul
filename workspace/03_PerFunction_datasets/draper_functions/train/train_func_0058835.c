cpld_set_led_id(struct hns_mac_cb *mac_cb,
		    enum hnae_led_state status)
{
	switch (status) {
	case HNAE_LED_ACTIVE:
		mac_cb->cpld_led_value = dsaf_read_b(mac_cb->cpld_vaddr);
		dsaf_set_bit(mac_cb->cpld_led_value, DSAF_LED_ANCHOR_B,
			     CPLD_LED_ON_VALUE);
		dsaf_write_b(mac_cb->cpld_vaddr, mac_cb->cpld_led_value);
		return 2;
	case HNAE_LED_INACTIVE:
		dsaf_set_bit(mac_cb->cpld_led_value, DSAF_LED_ANCHOR_B,
			     CPLD_LED_DEFAULT_VALUE);
		dsaf_write_b(mac_cb->cpld_vaddr, mac_cb->cpld_led_value);
		break;
	default:
		break;
	}

	return 0;
}
