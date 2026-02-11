gcmHash_DestroyContext(gcmHashContext *ghash, PRBool freeit)
{
    mp_clear(&ghash->H);
    mp_clear(&ghash->X);
    mp_clear(&ghash->C_i);
    MP_DIGITS(&ghash->H) = 0;
    MP_DIGITS(&ghash->X) = 0;
    MP_DIGITS(&ghash->C_i) = 0;
    if (freeit) {
	PORT_Free(ghash);
    }
}
