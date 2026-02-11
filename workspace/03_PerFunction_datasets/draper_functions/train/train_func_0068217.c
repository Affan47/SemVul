to_line(cp)
int cp;
{
    int tdx,line;
    tdx = 0;
    line = 0;
    while (tdx <= cp) {
	tdx = 1+fseekeol(tdx);
	line++;
    }
    return(line);
}
