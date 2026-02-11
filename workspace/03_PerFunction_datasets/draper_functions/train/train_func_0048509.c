add_time_stg( char *ps, struct timeval *ptv )
{
    time_t curtime;
    struct tm * ptm;
    curtime = (ptv->tv_sec & 0xffffffff);
    ptm = localtime(&curtime);
    if (ptm) {
        strftime(EndBuf(ps),128,"%H:%M:%S",ptm);
    }
}
