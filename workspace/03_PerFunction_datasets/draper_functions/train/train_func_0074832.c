get_tag(Octstr *body, Octstr *tag, Octstr **value, long pos, int nostrip) {
    long start, end;
    int taglen;
    Octstr *tmp;

    tmp = octstr_create("<");
    octstr_append(tmp, tag);
    octstr_append(tmp, octstr_imm(">"));
    taglen = octstr_len(tmp);

    start = octstr_search(body, tmp, pos);
    octstr_destroy(tmp);
    if(start != -1) {
	tmp = octstr_create("</");
	octstr_append(tmp, tag);
	octstr_append(tmp, octstr_imm(">"));

	end = octstr_search(body, tmp, start);
	octstr_destroy(tmp);
	if(end != -1) {
	    octstr_destroy(*value);
	    *value = octstr_copy(body, start + taglen, end - start - taglen);
	    if(nostrip == 0) {
		octstr_strip_blanks(*value);
		debug("sms", 0, "XMLParsing: tag <%s> value <%s>", octstr_get_cstr(tag),
			octstr_get_cstr(*value));
	    }
	    return end + taglen + 1;
	} else {
	    debug("sms", 0, "XMLParsing: end tag </%s> not found", octstr_get_cstr(tag));
	    return -1;
	}
    } else {

	return -1;
    }
}
