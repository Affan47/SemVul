min_gain(lzo_uint ahead, lzo_uint lit1, lzo_uint lit2, int l1, int l2, int l3)
{
    lzo_int lazy_match_min_gain = 0;

    assert (ahead >= 1);
    lazy_match_min_gain += ahead;

#if 0
    if (l3 > 0)
        lit2 -= ahead;
#endif

    if (lit1 <= 3)
        lazy_match_min_gain += (lit2 <= 3) ? 0 : 2;
    else if (lit1 <= 18)
        lazy_match_min_gain += (lit2 <= 18) ? 0 : 1;

    lazy_match_min_gain += (l2 - l1) * 2;
    if (l3 > 0)
        lazy_match_min_gain -= (ahead - l3) * 2;

    if (lazy_match_min_gain < 0)
        lazy_match_min_gain = 0;

#if 0
    if (l1 == 2)
        if (lazy_match_min_gain == 0)
            lazy_match_min_gain = 1;
#endif

    return lazy_match_min_gain;
}
