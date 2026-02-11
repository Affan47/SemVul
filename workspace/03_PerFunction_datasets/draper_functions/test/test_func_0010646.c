SITEwrite(SITE *sp, const char *text)
{
    static char		PREFIX[] = { EXP_CONTROL, '\0' };
    struct buffer       *bp;

    if (sp->Buffered)
	bp = &sp->Buffer;
    else {
	if (sp->Channel == NULL)
	    return;
	sp->Channel->LastActive = Now.tv_sec;
	bp = &sp->Channel->Out;
    }
    buffer_append(bp, PREFIX, strlen(PREFIX));
    buffer_append(bp, text, strlen(text));
    buffer_append(bp, "\n", 1);
    if (sp->Channel != NULL)
	WCHANadd(sp->Channel);
}
