alphabet (int set, int index)
{

    if (h_alphabet != 0) {

	zbyte c;

	zword addr = h_alphabet + 26 * set + index;
	LOW_BYTE (addr, c)

	return translate_from_zscii (c);

    } else

	if (set == 0)
	    return 'a' + index;
	else if (set == 1)
	    return 'A' + index;
	else if (h_version == V1)
	    return " 0123456789.,!?_#'\"/\\<-:()"[index];
	else
	    return " ^0123456789.,!?_#'\"/\\-:()"[index];

}
