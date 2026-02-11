_unmarshal_uchar_array(unsigned char **pData,
                                  unsigned int *pLenRemain,
                                  unsigned char *dest,
                                  int count)
{
        if (count <= 0  ||  (unsigned int)count > *pLenRemain)
        return 0;
    memcpy(dest, (*pData), count);
    *pData += count;
    *pLenRemain -= count;
    return 1;
}
