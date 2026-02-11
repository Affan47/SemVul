dsc_parse_cmyk_custom_colour(CDSC *dsc)
{
    unsigned int i, n;
    CDSCCOLOUR *pcolour;
    char colourname[MAXSTR];
    float cyan, magenta, yellow, black;
    GSBOOL blank_line;
    if (IS_DSC(dsc->line, "%%CMYKCustomColor:"))
	n = 18;
    else if (IS_DSC(dsc->line, "%%+"))
	n = 3;
    else
	return CDSC_ERROR;

    memset(&colourname, 0, sizeof(colourname));


    do {
	blank_line = TRUE;
	for (i=n; i<dsc->line_length; i++) {
	    if (!IS_WHITE_OR_EOL(dsc->line[i])) {
		blank_line = FALSE;
		break;
	    }
	}
	if (blank_line)
	    break;
	else {
	    cyan = magenta = yellow = black = 0.0;
	    cyan = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
	    n += i;
	    if (i)
		magenta = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
	    n += i;
	    if (i)
		yellow = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
	    n += i;
	    if (i)
		black = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
	    n += i;
	    if (i)
		dsc_copy_string(colourname, sizeof(colourname),
		    dsc->line+n, dsc->line_length-n, &i);
	    n+=i;
	    if (i && strlen(colourname)) {
		if ((pcolour = dsc_find_colour(dsc, colourname)) == NULL) {
		    pcolour = (CDSCCOLOUR *)
			dsc_memalloc(dsc, sizeof(CDSCCOLOUR));
		    if (pcolour == NULL)
			return CDSC_ERROR;
		    memset(pcolour, 0, sizeof(CDSCCOLOUR));
		    pcolour->name = dsc_alloc_string(dsc,
			colourname, (int)strlen(colourname));
	            pcolour->type = CDSC_COLOUR_UNKNOWN;
		    if (dsc->colours == NULL)
			dsc->colours = pcolour;
		    else {
			CDSCCOLOUR *this_colour = dsc->colours;
			while (this_colour->next)
			    this_colour = this_colour->next;
			this_colour->next = pcolour;
		    }
		}
		pcolour->custom = CDSC_CUSTOM_COLOUR_CMYK;
		pcolour->cyan = cyan;
		pcolour->magenta = magenta;
		pcolour->yellow = yellow;
		pcolour->black = black;
	    }
	}
    } while (i != 0);
    return CDSC_OK;
}
