filelen(ptr)
truc *ptr;
{
    FILE *fil;
    struct stream *strm;
    long pos, len;
    int mode;

    strm = STREAMPTR(ptr);
    mode = strm->mode;
    if(mode == NOSTREAM || (mode & DEVICE))
        return(-1);
    fil = strm->file;
    pos = ftell(fil);
    if(mode & OUTSTREAM)
        return(pos);
    else {
        fseek(fil,0L,2);
        len = ftell(fil);
        fseek(fil,pos,0);
        return(len);
    }
}
