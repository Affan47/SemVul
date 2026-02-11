chanmessage(int status, int c1, int c2)
{
    int chan = status & 0xf;

    if (!cut_beginning()) nochanmsg = 0;

    if (ctocopy[chan])
	switch (status & 0xf0) {
	case 0x80:
	    copy_noteoff(chan, c1, c2);
	    break;
	case 0x90:
	    copy_noteon(chan, c1, c2);
	    break;
	case 0xa0:
	    copy_pressure(chan, c1, c2);
	    break;
	case 0xb0:
	    copy_parameter(chan, c1, c2);
	    break;
	case 0xe0:
	    copy_pitchbend(chan, c1, c2);
	    break;
	case 0xc0:
	    copy_program(chan, c1);
	    break;
	case 0xd0:
	    copy_chanpressure(chan, c1);
	    break;
	}
}
