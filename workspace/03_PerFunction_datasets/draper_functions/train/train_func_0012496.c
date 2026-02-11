DER_TimeToUTCTimeArena(PLArenaPool* arenaOpt, SECItem *dst, PRTime gmttime)
{
    PRExplodedTime printableTime;
    unsigned char *d;

    if ( (gmttime < January1st1950) || (gmttime >= January1st2050) ) {
        PORT_SetError(SEC_ERROR_INVALID_ARGS);
        return SECFailure;
    }

    dst->len = 13;
    if (arenaOpt) {
        dst->data = d = (unsigned char*) PORT_ArenaAlloc(arenaOpt, dst->len);
    } else {
        dst->data = d = (unsigned char*) PORT_Alloc(dst->len);
    }
    dst->type = siUTCTime;
    if (!d) {
	return SECFailure;
    }


    PR_ExplodeTime(gmttime, PR_GMTParameters, &printableTime);


    printableTime.tm_month++;


    printableTime.tm_year %= 100;

    d[0] = HIDIGIT(printableTime.tm_year);
    d[1] = LODIGIT(printableTime.tm_year);
    d[2] = HIDIGIT(printableTime.tm_month);
    d[3] = LODIGIT(printableTime.tm_month);
    d[4] = HIDIGIT(printableTime.tm_mday);
    d[5] = LODIGIT(printableTime.tm_mday);
    d[6] = HIDIGIT(printableTime.tm_hour);
    d[7] = LODIGIT(printableTime.tm_hour);
    d[8] = HIDIGIT(printableTime.tm_min);
    d[9] = LODIGIT(printableTime.tm_min);
    d[10] = HIDIGIT(printableTime.tm_sec);
    d[11] = LODIGIT(printableTime.tm_sec);
    d[12] = 'Z';
    return SECSuccess;
}
