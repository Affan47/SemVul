CheckAbbrevs(const char *Buffer)
{
    long i;
    char *TmpPtr;
    const char *AbbPtr;

    if (INUSE(emInterWord))
    {
        TmpPtr = TmpBuffer + Abbrev.MaxLen + 2;
        *TmpPtr = 0;
        AbbPtr = Buffer;

        for (i = Abbrev.MaxLen; i >= 0; i--)
        {
            *--TmpPtr = *AbbPtr--;
            if (!isalpha((unsigned char)*AbbPtr) && HasWord(TmpPtr, &Abbrev))
                PSERR(Buffer - Buf + 1, 1, emInterWord);
            if (!*AbbPtr)
                break;
        }
    }
}
