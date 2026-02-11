alma_out(fp, format)
     FILE   *fp;
     int    format;
{
    int   indi, len;
    char  filename[TOKENNUM];
    FILE *outfile;

    Cpystr(filename, data.alma.id);
    for(indi=0, len=Lenstr(filename); indi<len; indi++)
        if(!isalnum(filename[indi])) filename[indi] = '_';
    Catstr(filename, ".EMBL");

    outfile = alma_out_entry_header(fp, data.alma.id, filename, format);
    alma_out_gaps(fp);

    return outfile;
}
