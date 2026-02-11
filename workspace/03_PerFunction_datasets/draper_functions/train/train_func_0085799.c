ParseIFF(struct IFFHandle * iff, long control)
{
    unsigned long i;
    uint32_t temp;

    if (control != IFFPARSE_SCAN) {
        D(bug("ParseIFF!=IFFPARSE_SCAN non implementato!\n"));
        return 1L;
    }

    for (;;)
    {
        temp = fread_u32(iff->iff_Stream);
        if (feof(iff->iff_Stream) || ferror(iff->iff_Stream))
            return 1L;

        for (i = 0; i < iff->iff_Stops; i++)
        {
            if (temp == (uint32_t)iff->stops[i * 2 + 1])
            {
                iff->Current.cn_ID = temp;
                temp = fread_u32(iff->iff_Stream);
                iff->Current.cn_Size = temp;
                return 0L;
            }
        }
        fseek(iff->iff_Stream, -2, SEEK_CUR);
    }
}
