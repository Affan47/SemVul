ReadChunkHead(FILE* f, FOURCC* ID, DWORD* size)
{
    if (!fread(ID,sizeof(FOURCC),1,f)) return(FALSE);
    if (!fread(size,sizeof(DWORD),1,f)) return(FALSE);
    *size = SWAP4(*size);
    return(TRUE);
}
