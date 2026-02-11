at2_format_address_field(Octstr *msisdn)
{
    int ntype = PNT_UNKNOWN;
    Octstr *out = octstr_create("");
    Octstr *temp = octstr_duplicate(msisdn);

    octstr_strip_blanks(temp);


    if (strncmp(octstr_get_cstr(msisdn), "+", 1) == 0) {
	octstr_delete(temp, 0, 1);
        ntype = PNT_INTER;
    } else if (strncmp(octstr_get_cstr(msisdn), "00", 2) == 0) {
        octstr_delete(temp, 0, 2);
        ntype = PNT_INTER;
    }


    octstr_append_char(out, octstr_len(temp));


    octstr_append_char(out, 0x80  |
			    0x01  |
			    (ntype == PNT_INTER ? 0x10 : 0x00)
			    );


    while (out != NULL && octstr_len(temp) > 0) {
	int digit1, digit2;

	digit1 = octstr_get_char(temp,0) - 48;
        digit2 = octstr_get_char(temp,1) - '0';
        if (digit2 < 0)
	    digit2 = 0x0F;
        if(digit1 >= 0 && digit1 < 16 && digit2 < 16) {
            octstr_append_char(out, (digit2 << 4) | digit1);
        }
        else {
            O_DESTROY(out);
            out = NULL;
        }
        octstr_delete(temp, 0, 2);
    }

    O_DESTROY(temp);
    return out;
}
