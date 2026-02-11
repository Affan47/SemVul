GetFloat(ScanfState *state)
{
    char buf[FMAX + 1], *p;
    int ch;
    PRBool seenDigit = PR_FALSE;

    if (state->width == 0 || state->width > FMAX) {
        state->width = FMAX;
    }
    p = buf;
    GET_IF_WITHIN_WIDTH(state, ch);
    if (WITHIN_WIDTH(state) && (ch == '+' || ch == '-')) {
        *p++ = ch;
        GET_IF_WITHIN_WIDTH(state, ch);
    }
    while (WITHIN_WIDTH(state) && isdigit(ch)) {
        *p++ = ch;
        GET_IF_WITHIN_WIDTH(state, ch);
        seenDigit = PR_TRUE;
    }
    if (WITHIN_WIDTH(state) && ch == DECIMAL_POINT) {
        *p++ = ch;
        GET_IF_WITHIN_WIDTH(state, ch);
        while (WITHIN_WIDTH(state) && isdigit(ch)) {
            *p++ = ch;
            GET_IF_WITHIN_WIDTH(state, ch);
            seenDigit = PR_TRUE;
        }
    }


    if (WITHIN_WIDTH(state) && (ch == 'e' || ch == 'E') && seenDigit) {
        *p++ = ch;
        GET_IF_WITHIN_WIDTH(state, ch);
        if (WITHIN_WIDTH(state) && (ch == '+' || ch == '-')) {
            *p++ = ch;
            GET_IF_WITHIN_WIDTH(state, ch);
        }
        while (WITHIN_WIDTH(state) && isdigit(ch)) {
            *p++ = ch;
            GET_IF_WITHIN_WIDTH(state, ch);
        }
    }
    if (WITHIN_WIDTH(state)) {
        UNGET(state, ch);
    }
    if (!seenDigit) {
        return PR_FAILURE;
    }
    *p = '\0';
    if (state->assign) {
        PRFloat64 dval = PR_strtod(buf, NULL);

        state->converted = PR_TRUE;
        if (state->sizeSpec == _PR_size_l) {
            *va_arg(state->ap, PRFloat64 *) = dval;
        } else if (state->sizeSpec == _PR_size_L) {
#if defined(OSF1) || defined(IRIX)
            *va_arg(state->ap, double *) = dval;
#else
            *va_arg(state->ap, long double *) = dval;
#endif
        } else {
            *va_arg(state->ap, float *) = (float) dval;
        }
    }
    return PR_SUCCESS;
}
