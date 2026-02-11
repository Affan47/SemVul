seqSelexPos(const AjPStr line, ajuint *begin, ajuint *end)
{
    ajuint pos = 0;
    ajuint len = 0;

    const char  *p;


    len  = ajStrGetLen(line) - 1;

    if(!len)
    {
        *begin=0;
        *end=0;

        return;
    }

    pos  = len -1;
    *end = (pos > *end) ? pos : *end;
    p = ajStrGetPtr(line);

    while(*p && *p!=' ')
        ++p;

    while(*p && *p==' ')
        ++p;

    if(p)
        pos = p - ajStrGetPtr(line);

    *begin = (pos < *begin) ? pos : *begin;

    ajDebug("seqSelexPos len:%u pos:%u begin:%u end:%u\n",
            len, pos, *begin, *end);

    return;
}
