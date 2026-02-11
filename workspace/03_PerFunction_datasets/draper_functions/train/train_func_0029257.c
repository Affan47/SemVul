cavan_touchpad_device_match(uint8_t *key_bitmask, uint8_t *abs_bitmask)
{
	if (test_bit(BTN_LEFT, key_bitmask) == 0 || \
		test_bit(BTN_RIGHT, key_bitmask) == 0 || \
		test_bit(BTN_TOUCH, key_bitmask) == 0 || \
		test_bit(ABS_X, abs_bitmask) == 0 || \
		test_bit(ABS_Y, abs_bitmask) == 0)
	{
		return false;
	}

	clean_bit(BTN_LEFT, key_bitmask);
	clean_bit(BTN_RIGHT, key_bitmask);
	clean_bit(BTN_MIDDLE, key_bitmask);
	clean_bit(BTN_TOUCH, key_bitmask);
	clean_bit(ABS_X, abs_bitmask);
	clean_bit(ABS_Y, abs_bitmask);

	return true;
}
