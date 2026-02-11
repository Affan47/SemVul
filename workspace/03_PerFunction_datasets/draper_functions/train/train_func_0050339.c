opt_from_flag (unsigned char c)
{
    int i;

    for (i=0; flag_matches[i].c != '\0'; i++) {
	if (c == flag_matches[i].c) {
	    return flag_matches[i].o;
	}
    }

    return 0L;
}
