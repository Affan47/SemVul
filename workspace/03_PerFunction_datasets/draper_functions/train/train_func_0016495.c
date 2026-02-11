imon_parse_press_type(struct imon_context *ictx,
				 unsigned char *buf, u8 ktype)
{
	int press_type = 0;
	unsigned long flags;

	spin_lock_irqsave(&ictx->kc_lock, flags);


	if (ictx->kc == KEY_RESERVED && buf[0] == 0x02 && buf[3] == 0x00)
		ictx->kc = ictx->last_keycode;


	else if (ictx->kc == KEY_RESERVED && buf[0] == 0x68 && buf[1] == 0x82 &&
		 buf[2] == 0x81 && buf[3] == 0xb7)
		ictx->kc = ictx->last_keycode;


	else if (ictx->kc == KEY_RESERVED && buf[0] == 0x01 && buf[1] == 0x00 &&
		 buf[2] == 0x81 && buf[3] == 0xb7)
		ictx->kc = ictx->last_keycode;


	else if (ktype == IMON_KEY_MCE) {
		ictx->rc_toggle = buf[2];
		press_type = 1;


	} else if (ictx->kc == KEY_RESERVED)
		press_type = -EINVAL;


	else if (ictx->release_code)
		press_type = 0;


	else
		press_type = 1;

	spin_unlock_irqrestore(&ictx->kc_lock, flags);

	return press_type;
}
