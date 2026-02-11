tim_cpu()
{
 clock_t t=clock();


#ifndef CLOCKS_PER_SEC
#ifdef CLK_TCK
#define CLOCKS_PER_SEC CLK_TCK
#else

#define CLOCKS_PER_SEC (1000000L)
#endif
#endif


 if (t == -1)
    return 0.0;
 else
    return ((float) t) / ((float) CLOCKS_PER_SEC);
}
