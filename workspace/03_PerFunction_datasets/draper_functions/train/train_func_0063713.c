FindBaud(char *pcMode)
#else
FindBaud(pcMode)
    char *pcMode;
#endif
{
    int i;

    for (i = 0; i < sizeof(baud) / sizeof(struct baud); ++i) {
	if (strcmp(pcMode, baud[i].acrate) == 0)
	    return baud + i;
    }
    return (BAUD *)0;
}
