parse_global_phone_number(Octstr **address, long pos)
{
    unsigned char c;

    while ((c = octstr_get_char(*address, pos)) != '+' && pos >= 0) {
         if (!isdigit(c) && c != '-' && c != '.') {
             debug("wap.push.pap.compiler", 0, "PAP COMPILER: wrong separator"
                   " in a phone number (- and . allowed)");
             return -2;
	 } else {
	     --pos;
         }
    }

    if (pos == 0) {
        debug("wap.push.pap.compiler", 0, "PAP COMPILER:a phone number must"
              " start with +");
        return -2;
    }

    if (pos > 0)
        --pos;

    pos = drop_character(address, pos);

    return pos;
}
