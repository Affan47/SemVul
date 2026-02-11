unexpected(keyword_id_t innerblock, keyword_id_t outerblock)
{


    switch (outerblock) {
    case THEN:
	eprintf("unexpected /%s in IF body", keyword_label(innerblock));
	break;
    case DO:
	eprintf("unexpected /%s in WHILE body", keyword_label(innerblock));
	break;
    default:
	eprintf("unexpected /%s in %s block", keyword_label(innerblock),
	    outerblock ? keyword_label(outerblock) : "outer");
    }
}
