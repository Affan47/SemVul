lookup_text (int padding, zword dct)
{
    zword entry_addr;
    zword entry_count;
    zword entry;
    zword addr;
    zbyte entry_len;
    zbyte sep_count;
    int resolution = (h_version <= V3) ? 2 : 3;
    int entry_number;
    int lower, upper;
    int i;
    bool sorted;

    encode_text (padding);

    LOW_BYTE (dct, sep_count)
    dct += 1 + sep_count;
    LOW_BYTE (dct, entry_len)
    dct += 1;
    LOW_WORD (dct, entry_count)
    dct += 2;

    if ((short) entry_count < 0) {

	entry_count = - (short) entry_count;
	sorted = FALSE;

    } else sorted = TRUE;

    lower = 0;
    upper = entry_count - 1;

    while (lower <= upper) {

	if (sorted)
	    entry_number = (lower + upper) / 2;
	else
	    entry_number = lower;

	entry_addr = dct + entry_number * entry_len;


	addr = entry_addr;

	for (i = 0; i < resolution; i++) {
	    LOW_WORD (addr, entry)
	    if (encoded[i] != entry)
		goto continuing;
	    addr += 2;
	}

	return entry_addr;

    continuing:

	if (sorted)

	    if (encoded[i] > entry)
		lower = entry_number + 1;
	    else
		upper = entry_number - 1;

	else lower++;

    }


    if (padding == 0x05)
	return 0;

    entry_number = (padding == 0x00) ? lower : upper;

    if (entry_number == -1 || entry_number == entry_count)
	return 0;

    return dct + entry_number * entry_len;

}
