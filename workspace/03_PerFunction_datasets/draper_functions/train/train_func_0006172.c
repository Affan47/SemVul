init(void)
{
    int i;

    if (!regressionTestOption && (debugOption||sectionTraceOption||singleStepOption)) {
        char str[80];
        output("<Hi! This is Alan interactive fiction interpreter Arun,");
        sprintf(str, "version %ld.%ld%s%ld",
                (long)alan.version.version,
                (long)alan.version.revision,
                alan.version.state[0]=='\0'?".":alan.version.state,
                (long)alan.version.correction);
        output(str);
	if (BUILD != 0)
	    sprintf(str, "- build %d!>$n", BUILD);
	else
	    sprintf(str, "!>$n");
	output(str);
    }


    eventQueueTop = 0;
    initStaticData();
    initDynamicData();
    initParsing();
    checkDebug();

    getPageSize();


    for (i = 0; i < dictionarySize; i++)
        if (isConjunction(i)) {
            conjWord = i;
            break;
        }


    if (debugOption)
        debug(FALSE, 0, 0);
    else
        clear();

    start();
}
