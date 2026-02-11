datalook(long pos)
{
    if (pos<0 || pos >= flen) return(0);
    return(data[pos]);
}
