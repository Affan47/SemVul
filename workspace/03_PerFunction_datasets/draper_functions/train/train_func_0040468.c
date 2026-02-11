waitFor(ATResponse wanted, long ms)
{
    for (;;) {
	ATResponse response = atResponse(rbuf, ms);
	if (response == wanted)
	    return (true);
	switch (response) {
	case AT_TIMEOUT:
	case AT_EMPTYLINE:
	case AT_ERROR:
	case AT_NOCARRIER:
	case AT_NODIALTONE:
	case AT_NOANSWER:
	case AT_RING:
	    modemTrace("MODEM %s", ATresponses[response]);
	case AT_OK:
	    return (false);
	case AT_FHNG:

	    { char buf[1024]; (void) atResponse(buf, 2*1000); }
	    return (isNormalHangup());
	}
    }
}
