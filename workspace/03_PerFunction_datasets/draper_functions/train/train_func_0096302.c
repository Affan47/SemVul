open_pnm_input_file(context *con)
{
    int c, max, one=1;

    rewind(con->file);
    c=get_uint8(con);
    if (c!='P')
        error("unexpected character 0x%02x (%c) at start of PNM file %s", c, c, con->name);
    switch (c=get_uint8(con)) {
        case '1' :
        case '2' :
        case '3' :
        case '4' : error("unsupported PNM file type P%c in PNM file %s", c, con->name);
        case '5' : con->ncomp = 1; break;
        case '6' : con->ncomp = 3; break;
        default : error("unexpected character 0x%02x (%c) following 'P' in PNM file %s", c, c, con->name);
    }

    con->wid = read_pnm_number(con);
    if (con->wid<=0)
        error("invalid image width %d in PNM file %s",con->wid, con->name);
    con->hei = read_pnm_number(con);
    if (con->hei<=0)
        error("invalid image height %d in PNM file %s", con->hei, con->name);
    max=read_pnm_number(con);
    if (max>=0x10000)
        error("invalid maximum value 0x%02x (%d) in PNM file %s", max, max, con->name);
    if (max<0x100) con->swap = 0;
    else con->swap = *(char*)&one==1;
    for (con->bpi=1; max>(1<<con->bpi); con->bpi++);

    con->nlines = con->hei;
}
