setup_baud_rate (int baud_rate)
{
	switch (baud_rate)
	{

#if defined(B921600)
	case 921600:
	    baud_rate = B921600;
	    break;
#endif
#if defined(B460800)
	case 460800:
	    baud_rate = B460800;
	    break;
#endif
	case 230400:
	    baud_rate = B230400;
	    break;
	case 115200:
	    baud_rate = B115200;
	    break;
	case 57600:
	    baud_rate = B57600;
	    break;
	case 38400:
	    baud_rate = B38400;
	    break;
	case 19200:
	    baud_rate = B19200;
	    break;
	case 9600:
		baud_rate = B9600;
		break;
	case 4800:
	    baud_rate = B4800;
		break;
	case 2400:
	    baud_rate = B2400;
		break;
	case 1800:
	    baud_rate = B1800;
		break;
	case 1200:
	    baud_rate = B1200;
		break;
	case 600:
	    baud_rate = B600;
	    break;
	case 300:
	    baud_rate = B300;
	    break;
	case 200:
	    baud_rate = B200;
	    break;
	case 150:
	    baud_rate = B150;
	    break;
	case 134:
	    baud_rate = B134;
	    break;
	case 110:
	    baud_rate = B110;
	    break;
	case 75:
	    baud_rate = B75;
	    break;
	case 50:
	case 0:
	default:
	    baud_rate = -1;
		break;
	}
	return baud_rate;
}
