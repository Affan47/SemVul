dsc_parse_pages(CDSC *dsc)
{
    int ip, io;
    unsigned int i;
    char *p;
    int n;
    if ((dsc->page_pages != 0) && (dsc->scan_section == scan_comments)) {
	int rc = dsc_error(dsc, CDSC_MESSAGE_DUP_COMMENT, dsc->line,
		dsc->line_length);
	switch (rc) {
	    case CDSC_RESPONSE_OK:
	    case CDSC_RESPONSE_CANCEL:
		return CDSC_OK;
	    case CDSC_RESPONSE_IGNORE_ALL:
		return CDSC_NOTDSC;
	}
    }
    if ((dsc->page_pages != 0) && (dsc->scan_section == scan_trailer)) {
	int rc = dsc_error(dsc, CDSC_MESSAGE_DUP_TRAILER, dsc->line,
		dsc->line_length);
	switch (rc) {
	    case CDSC_RESPONSE_OK:
	    case CDSC_RESPONSE_CANCEL:
		break;
	    case CDSC_RESPONSE_IGNORE_ALL:
		return CDSC_NOTDSC;
	}
    }

    n = IS_DSC(dsc->line, "%%+") ? 3 : 8;
    while (IS_WHITE(dsc->line[n]))
	n++;
    p = dsc->line + n;
    if (COMPARE(p, "atend")) {
	int rc = dsc_error(dsc, CDSC_MESSAGE_ATEND, dsc->line, dsc->line_length);
	switch (rc) {
	    case CDSC_RESPONSE_OK:


		break;
	    case CDSC_RESPONSE_CANCEL:

		break;
	    case CDSC_RESPONSE_IGNORE_ALL:
		return CDSC_NOTDSC;
	}
    }
    else if (COMPARE(p, "(atend)")) {


    }
    else {
	ip = dsc_get_int(dsc->line+n, dsc->line_length-n, &i);
        if (i) {
	    n+=i;
	    dsc->page_pages = ip;
	    io = dsc_get_int(dsc->line+n, dsc->line_length-n, &i);
	    if (i) {


		if (dsc->page_order == CDSC_ORDER_UNKNOWN)
		    switch (io) {
			case -1:
			    dsc->page_order = CDSC_DESCEND;
			    break;
			case 0:
			    dsc->page_order = CDSC_SPECIAL;
			    break;
			case 1:
			    dsc->page_order = CDSC_ASCEND;
			    break;
		    }
	    }
	}
	else {
	    int rc = dsc_error(dsc, CDSC_MESSAGE_INCORRECT_USAGE, dsc->line,
		dsc->line_length);
	    switch (rc) {
		case CDSC_RESPONSE_OK:
		case CDSC_RESPONSE_CANCEL:

		    break;
		case CDSC_RESPONSE_IGNORE_ALL:
		    return CDSC_NOTDSC;
	    }
	}
    }
    return CDSC_OK;
}
