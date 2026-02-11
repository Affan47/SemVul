SwapBytesInWords(short *ptr, int short_words)
{
    unsigned long val;
    unsigned long *p = (unsigned long *) ptr;

#ifndef lint
# if defined(CHAR_BIT)
#  if CHAR_BIT != 8
#   error CHAR_BIT != 8
#  endif
# else
#  error can not determine number of bits in a char
# endif
#endif

    assert(sizeof(short) == 2);


#if defined(SIZEOF_UNSIGNED_LONG) && SIZEOF_UNSIGNED_LONG == 4
    for (; short_words >= 2; short_words -= 2, p++) {
        val = *p;
        *p = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
    }
    ptr = (short *) p;
    for (; short_words >= 1; short_words -= 1, ptr++) {
        val = *ptr;
        *ptr = (short) (((val << 8) & 0xFF00) | ((val >> 8) & 0x00FF));
    }
#elif defined(SIZEOF_UNSIGNED_LONG) && SIZEOF_UNSIGNED_LONG == 8
    for (; short_words >= 4; short_words -= 4, p++) {
        val = *p;
        *p = ((val << 8) & 0xFF00FF00FF00FF00) | ((val >> 8) & 0x00FF00FF00FF00FF);
    }
    ptr = (short *) p;
    for (; short_words >= 1; short_words -= 1, ptr++) {
        val = *ptr;
        *ptr = ((val << 8) & 0xFF00) | ((val >> 8) & 0x00FF);
    }
#else
# ifdef SIZEOF_UNSIGNED_LONG
#  warning Using unoptimized SwapBytesInWords().
# endif
    for (; short_words >= 1; short_words -= 1, ptr++) {
        val = *ptr;
        *ptr = ((val << 8) & 0xFF00) | ((val >> 8) & 0x00FF);
    }
#endif

    assert(short_words == 0);
}
