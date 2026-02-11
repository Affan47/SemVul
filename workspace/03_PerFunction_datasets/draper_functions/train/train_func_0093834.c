scan()
{
    int ch;

    check_fall_thru(0);
    check_notreached(0);

    while (1) {
	ch = scan_0(0);
	if (ch == '#') {
	    int cpp = 1;
	    do {
		ch = scan_0(cpp);
		if (cpp == 1 && ch == TKN_INCLUDE)
		    cpp = 2;
		if (ch == '\\')
		    scan_0(cpp);
	    } while ((ch != '\n') && (ch != EOF));
	}
	else if (ch == '\\') {
	    message("Unexpected character '\\'");
	}
	else if (ch != '\n')
	    return ch;
    }
}
