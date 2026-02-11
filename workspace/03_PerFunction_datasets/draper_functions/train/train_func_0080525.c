clean_check(void)
{
    int x;
    char *s;

    if (still_ppp()) {
	if (ioctl(ppp_fd, PPPIOCGFLAGS, (caddr_t) &x) == 0) {
	    s = NULL;
	    switch (~x & (SC_RCV_B7_0|SC_RCV_B7_1|SC_RCV_EVNP|SC_RCV_ODDP)) {
	    case SC_RCV_B7_0:
		s = "all had bit 7 set to 1";
		break;

	    case SC_RCV_B7_1:
		s = "all had bit 7 set to 0";
		break;

	    case SC_RCV_EVNP:
		s = "all had odd parity";
		break;

	    case SC_RCV_ODDP:
		s = "all had even parity";
		break;
	    }

	    if (s != NULL) {
		warn("Receive serial link is not 8-bit clean:");
		warn("Problem: %s", s);
	    }
	}
    }
}
