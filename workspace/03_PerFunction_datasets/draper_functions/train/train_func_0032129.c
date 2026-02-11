parse_dom_fragment(Octstr **address, long pos)
{
    unsigned char c;

    if (pos >= 0) {
        if (isalnum(octstr_get_char(*address, pos))) {
	    pos = drop_character(address, pos);
        } else
	    return -2;
    }

    while ((c = octstr_get_char(*address, pos)) != '@' &&
               octstr_get_char(*address, pos) != '.' && pos >= 0)  {
        if (isalnum(c) || c == '-') {
	    pos = drop_character(address, pos);
        } else
	    return -2;
    }

    return pos;
}
