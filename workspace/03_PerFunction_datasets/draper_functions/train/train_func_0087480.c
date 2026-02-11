return_mostly_to_neutral(htmloutput *ho)
{
    if (ho->fp) {
	if (ho->state == HO_IN_EMPTY_TAG && is_xhtml(ho->ver)) {
	    fprintf(ho->fp, " />");
	} else if (ho->state == HO_IN_EMPTY_TAG || ho->state == HO_IN_TAG) {
	    fprintf(ho->fp, ">");
	}
    }

    ho->state = HO_NEUTRAL;
}
