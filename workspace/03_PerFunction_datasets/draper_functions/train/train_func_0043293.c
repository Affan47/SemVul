SendChunkHeader (BYTE *szStr, DWORD dwSize, DWORD dwChunkType, DWORD dwNumItems)
{
    for (int j = 3, i = 0; j >= 0; j--)
    {
        szStr[i] = (BYTE) ((dwSize >> (8 * (j))) & 0xFF);
        szStr[4+i] = (BYTE) ((dwChunkType >> (8 * (j))) & 0xFF);
        szStr[8+i] = (BYTE) ((dwNumItems >> (8 * (j))) & 0xFF);
        i++;
    }

    szStr[12] = (BYTE) (((dwNumItems * 12) & 0xFF00) >> 8);
    szStr[13] = (BYTE) (((dwNumItems * 12) & 0x00FF));

    szStr[14] = 'Z';
    szStr[15] = 'Z';
    return 16;
}
