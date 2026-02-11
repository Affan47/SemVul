common_keypress_handler(int key)
{
	switch (key) {
		case 0x01:
			request_abort_suspend();
			break;
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07:
		case 0x08:
		case 0x09:
		case 0x0a:
		case 0x0b:
			console_loglevel = (key - 1)%10;
			set_console_loglevel(0);
			break;
		case 0x13:
			toggle_reboot();
			break;
		case 0x18:
			toggle_poweroff();
			break;
		case 0x19:
			toggle_pause();
			break;
		case 0x1F:
			toggle_singlestep();
			break;
		case 0x26:
			toggle_log_all();
			break;
		case 0x39:
			notify_space_pressed();
			break;
		case 0x3B:
		case 0x3C:
		case 0x3D:
		case 0x3E:
		case 0x3F:
		case 0x40:
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x44:
		case 0x57:
		case 0x58:
			toggle_debug_state(key);
			break;
		case 0x2D:
			next_ops = 3;
			break;
		case 0x21:
			next_ops = 2;
			break;
		case 0x16:
			next_ops = 1;
			break;
		default:
			return 0;
	}
	return 1;
}
