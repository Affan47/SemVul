floattime(void)
{


#ifdef HAVE_GETTIMEOFDAY
    {
        struct timeval t;
#ifdef GETTIMEOFDAY_NO_TZ
        if (gettimeofday(&t) == 0)
            return (double)t.tv_sec + t.tv_usec*0.000001;
#else
        if (gettimeofday(&t, (struct timezone *)NULL) == 0)
            return (double)t.tv_sec + t.tv_usec*0.000001;
#endif
    }

#endif
    {
#if defined(HAVE_FTIME)
        struct timeb t;
        ftime(&t);
        return (double)t.time + (double)t.millitm * (double)0.001;
#else
        time_t secs;
        time(&secs);
        return (double)secs;
#endif
    }
}
