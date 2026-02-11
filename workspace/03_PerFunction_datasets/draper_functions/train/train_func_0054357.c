alt_arc4random_uniform(unsigned int upper_bound)
{
    unsigned int r, min;

    if (upper_bound < 2U) {
        return 0U;
    }

#if (ULONG_MAX > 0xffffffffUL)
    min = (unsigned int) (0x100000000UL % upper_bound);
#else

    if (upper_bound > 0x80000000)
        min = 1 + ~upper_bound;
    else {

        min = ((0xffffffff - (upper_bound * 2)) + 1) % upper_bound;
    }
#endif


    for (;;) {
        r = alt_arc4random();
        if (r >= min) {
            break;
        }
    }

    return r % upper_bound;
}
