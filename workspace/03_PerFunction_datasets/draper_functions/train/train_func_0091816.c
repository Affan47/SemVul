close_chid(char *id)
{
    static time_t last = 0;
    static char current;
    char *curid;

    if (timeofday - last > 900 || id[0] == current)
	{
	    last = timeofday;
	    curid = get_chid();
	    current = curid[0];
	}
    if (id_alphabet[1 + alphabet_id[(unsigned char)current]] == id[1])
	    return 1;
    if (id[0] == current &&
	idtol(id, CHIDLEN) >= (timeofday % (u_int) pow(CHIDNB, CHIDLEN)))
	    return 1;
    return 0;
}
