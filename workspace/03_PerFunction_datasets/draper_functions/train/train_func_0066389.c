scanKeywords(struct S_cfgLine line[], int *lineanz, int *maxlen)
{
    while (1)
    {
        cstr keyword    = line[*lineanz].keyword;
        int  keywordlen;

        if (!keyword) break;
        keywordlen = strlen(keyword);
        if (keywordlen>*maxlen) *maxlen = keywordlen;
        (*lineanz)++;
    }
}
