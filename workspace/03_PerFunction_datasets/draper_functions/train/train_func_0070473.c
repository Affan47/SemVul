e1000e_id_led_init_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val;
	const u32 ledctl_mask = 0x000000FF;
	const u32 ledctl_on = E1000_LEDCTL_MODE_LED_ON;
	const u32 ledctl_off = E1000_LEDCTL_MODE_LED_OFF;
	u16 data, i, temp;
	const u16 led_mask = 0x0F;

	ret_val = hw->nvm.ops.valid_led_default(hw, &data);
	if (ret_val)
		return ret_val;

	mac->ledctl_default = er32(LEDCTL);
	mac->ledctl_mode1 = mac->ledctl_default;
	mac->ledctl_mode2 = mac->ledctl_default;

	for (i = 0; i < 4; i++) {
		temp = (data >> (i << 2)) & led_mask;
		switch (temp) {
		case ID_LED_ON1_DEF2:
		case ID_LED_ON1_ON2:
		case ID_LED_ON1_OFF2:
			mac->ledctl_mode1 &= ~(ledctl_mask << (i << 3));
			mac->ledctl_mode1 |= ledctl_on << (i << 3);
			break;
		case ID_LED_OFF1_DEF2:
		case ID_LED_OFF1_ON2:
		case ID_LED_OFF1_OFF2:
			mac->ledctl_mode1 &= ~(ledctl_mask << (i << 3));
			mac->ledctl_mode1 |= ledctl_off << (i << 3);
			break;
		default:

			break;
		}
		switch (temp) {
		case ID_LED_DEF1_ON2:
		case ID_LED_ON1_ON2:
		case ID_LED_OFF1_ON2:
			mac->ledctl_mode2 &= ~(ledctl_mask << (i << 3));
			mac->ledctl_mode2 |= ledctl_on << (i << 3);
			break;
		case ID_LED_DEF1_OFF2:
		case ID_LED_ON1_OFF2:
		case ID_LED_OFF1_OFF2:
			mac->ledctl_mode2 &= ~(ledctl_mask << (i << 3));
			mac->ledctl_mode2 |= ledctl_off << (i << 3);
			break;
		default:

			break;
		}
	}

	return 0;
}
