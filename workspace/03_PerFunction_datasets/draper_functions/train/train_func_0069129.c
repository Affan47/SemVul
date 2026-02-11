StrTime(time_t *ltime)
#else
StrTime(ltime)
    time_t *ltime;
#endif
{
    static char curtime[40];
    time_t tyme;

    tyme = time((time_t *)0);
    StrCpy(curtime, ctime(&tyme), sizeof(curtime));
    curtime[24] = '\000';
    if (ltime != NULL)
	*ltime = tyme;
    return (const char *)curtime;
}
