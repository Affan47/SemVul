VocSeekFile(
            int              n,
            VocInfo        *vi
            )
{
    return vi->writing ? -1 : fseek(vi->fp, vi->dataOffset + 3 + n, 0);
}
