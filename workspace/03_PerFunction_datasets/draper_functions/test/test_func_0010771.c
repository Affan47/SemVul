vty_telnet_option(vty_t *vty, unsigned char *buf, int nbytes)
{
	switch (buf[0]) {
	case SB:
		vty->sb_len = 0;
		vty->iac_sb_in_progress = 1;
		return 0;
		break;
	case SE:
	{
		if (!vty->iac_sb_in_progress)
			return 0;

		if ((vty->sb_len == 0) || (vty->sb_buf[0] == '\0')) {
			vty->iac_sb_in_progress = 0;
			return 0;
		}

		switch (vty->sb_buf[0]) {
		case TELOPT_NAWS:
			if (vty->sb_len != TELNET_NAWS_SB_LEN) {
				log_message(LOG_ERR, "RFC 1073 violation detected: telnet NAWS option "
						     "should send %d characters, but we received %lu"
						   , TELNET_NAWS_SB_LEN, (u_long)vty->sb_len);
			} else if (sizeof(vty->sb_buf) < TELNET_NAWS_SB_LEN) {
				log_message(LOG_ERR, "Bug detected: sizeof(vty->sb_buf) %lu < %d, "
						     "too small to handle the telnet NAWS option"
						   , (u_long)sizeof(vty->sb_buf), TELNET_NAWS_SB_LEN);
			} else {
				vty->width = ((vty->sb_buf[1] << 8)|vty->sb_buf[2]);
				vty->height = ((vty->sb_buf[3] << 8)|vty->sb_buf[4]);
			}
			break;
		}
		vty->iac_sb_in_progress = 0;
		return 0;
		break;
	}
	default:
		break;
	}

	return 1;
}
