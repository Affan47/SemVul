_InvT_odd_odd(int*a, int*b, int*c, int*d)
{
    int t1, t2;
    *d += *a;
    *c -= *b;
    t1 = *d >> 1;
    t2 = *c >> 1;
    *a -= t1;
    *b += t2;
    CHECK4(long_word_flag, *a, *b, *c, *d);

    *a -= ((*b)*3 + 3) >> 3;
    *b += ((*a)*3 + 3) >> 2;
    CHECK2(long_word_flag, *a, *b);
    *a -= ((*b)*3 + 4) >> 3;

    *b -= t2;
    CHECK2(long_word_flag, *a, *b);
    *a += t1;
    *c += *b;
    *d -= *a;

    *b = -*b;
    *c = -*c;
    CHECK4(long_word_flag, *a, *b, *c, *d);
}
