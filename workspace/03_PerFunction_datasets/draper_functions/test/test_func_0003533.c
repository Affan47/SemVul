get_piece_name(void)
{
    char c;
    int i;

    c = get_chx ();

    for (i = 0; i < NUM_OBJECTS; i++)
	if (piece_attr[i].sname == c) {
	    return i;
	}
    return NOPIECE;
}
