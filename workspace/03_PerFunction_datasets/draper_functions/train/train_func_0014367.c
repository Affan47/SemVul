mp_badd(const mp_int *a, const mp_int *b, mp_int *c)
{
    mp_digit *pa, *pb, *pc;
    mp_size ix;
    mp_size used_pa, used_pb;
    mp_err res = MP_OKAY;


    if (MP_USED(a) >= MP_USED(b)) {
        pa = MP_DIGITS(a);
        pb = MP_DIGITS(b);
        used_pa = MP_USED(a);
        used_pb = MP_USED(b);
    } else {
        pa = MP_DIGITS(b);
        pb = MP_DIGITS(a);
        used_pa = MP_USED(b);
        used_pb = MP_USED(a);
    }


    MP_CHECKOK( s_mp_pad(c, used_pa) );


    pc = MP_DIGITS(c);
    for (ix = 0; ix < used_pb; ix++) {
        (*pc++) = (*pa++) ^ (*pb++);
    }


    for (; ix < used_pa; ++ix) {
        *pc++ = *pa++;
    }

    MP_USED(c) = used_pa;
    MP_SIGN(c) = ZPOS;
    s_mp_clamp(c);

CLEANUP:
    return res;
}
