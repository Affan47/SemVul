tty_set_xaccm (ext_accm accm)
{
    if (!still_ppp())
	return;
    if (ioctl(ppp_fd, PPPIOCSXASYNCMAP, accm) < 0 && errno != ENOTTY) {
	if ( ! ok_error (errno))
	    warn("ioctl(set extended ACCM): %m (line %d)", __LINE__);
    }
}
