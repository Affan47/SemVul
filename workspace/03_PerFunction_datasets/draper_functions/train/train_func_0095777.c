Perl_grok_bin(pTHX_ const char *start, STRLEN *len_p, I32 *flags, NV *result)
{
    const char *s = start;
    STRLEN len = *len_p;
    UV value = 0;
    NV value_nv = 0;

    const UV max_div_2 = UV_MAX / 2;
    const bool allow_underscores = cBOOL(*flags & PERL_SCAN_ALLOW_UNDERSCORES);
    bool overflowed = FALSE;
    char bit;

    PERL_ARGS_ASSERT_GROK_BIN;

    if (!(*flags & PERL_SCAN_DISALLOW_PREFIX)) {


        if (len >= 1) {
            if (s[0] == 'b' || s[0] == 'B') {
                s++;
                len--;
            }
            else if (len >= 2 && s[0] == '0' && (s[1] == 'b' || s[1] == 'B')) {
                s+=2;
                len-=2;
            }
        }
    }

    for (; len-- && (bit = *s); s++) {
        if (bit == '0' || bit == '1') {


          redo:
            if (!overflowed) {
                if (value <= max_div_2) {
                    value = (value << 1) | (bit - '0');
                    continue;
                }


		Perl_ck_warner_d(aTHX_ packWARN(WARN_OVERFLOW),
				 "Integer overflow in binary number");
                overflowed = TRUE;
                value_nv = (NV) value;
            }
            value_nv *= 2.0;


            value_nv += (NV)(bit - '0');
            continue;
        }
        if (bit == '_' && len && allow_underscores && (bit = s[1])
            && (bit == '0' || bit == '1'))
	    {
		--len;
		++s;
                goto redo;
	    }
        if (!(*flags & PERL_SCAN_SILENT_ILLDIGIT))
            Perl_ck_warner(aTHX_ packWARN(WARN_DIGIT),
			   "Illegal binary digit '%c' ignored", *s);
        break;
    }

    if (   ( overflowed && value_nv > 4294967295.0)
#if UVSIZE > 4
	|| (!overflowed && value > 0xffffffff
	    && ! (*flags & PERL_SCAN_SILENT_NON_PORTABLE))
#endif
	) {
	Perl_ck_warner(aTHX_ packWARN(WARN_PORTABLE),
		       "Binary number > 0b11111111111111111111111111111111 non-portable");
    }
    *len_p = s - start;
    if (!overflowed) {
        *flags = 0;
        return value;
    }
    *flags = PERL_SCAN_GREATER_THAN_UV_MAX;
    if (result)
        *result = value_nv;
    return UV_MAX;
}
