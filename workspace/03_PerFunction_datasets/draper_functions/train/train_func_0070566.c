rt2500usb_blink_set(struct led_classdev *led_cdev,
			       unsigned long *delay_on,
			       unsigned long *delay_off)
{
	struct rt2x00_led *led =
	    container_of(led_cdev, struct rt2x00_led, led_dev);
	u16 reg;

	rt2500usb_register_read(led->rt2x00dev, MAC_CSR21, &reg);
	rt2x00_set_field16(&reg, MAC_CSR21_ON_PERIOD, *delay_on);
	rt2x00_set_field16(&reg, MAC_CSR21_OFF_PERIOD, *delay_off);
	rt2500usb_register_write(led->rt2x00dev, MAC_CSR21, reg);

	return 0;
}
