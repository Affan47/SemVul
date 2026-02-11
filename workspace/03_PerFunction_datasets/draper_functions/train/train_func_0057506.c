strecke(kreuz_coord, i)
AV* kreuz_coord;
int i;
{
#if defined(INT_SQRT) || defined(MAYBE_INT_SQRT)
    long a1, a2;
#else
    float a1, a2;
#endif
    SV *tmp1, *tmp2;

    tmp1 = SvRV(*av_fetch(kreuz_coord, i, 0));
    tmp2 = SvRV(*av_fetch(kreuz_coord, i+1, 0));

    a1 = SvIV(*(av_fetch((AV*)tmp1, 0, 0))) -
         SvIV(*(av_fetch((AV*)tmp2, 0, 0)));
    a2 = SvIV(*(av_fetch((AV*)tmp1, 1, 0))) -
         SvIV(*(av_fetch((AV*)tmp2, 1, 0)));
#if defined(INT_SQRT) || defined(MAYBE_INT_SQRT)
    return eyal(a1*a1 + a2*a2);
#else
#  ifdef USE_HYPOT

    return hypotf(a1,a2);
#  else
    return sqrtf(a1*a1 + a2*a2);
#  endif
#endif
}
