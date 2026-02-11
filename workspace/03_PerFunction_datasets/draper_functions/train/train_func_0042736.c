netsnmp_c64_check_for_32bit_wrap(struct counter64 *old_val,
                                 struct counter64 *new_val,
                                 int adjust)
{
    if( (NULL == old_val) || (NULL == new_val) )
        return -1;

    DEBUGMSGTL(("9:c64:check_wrap", "check wrap 0x%0lx.0x%0lx 0x%0lx.0x%0lx\n",
                old_val->high, old_val->low, new_val->high, new_val->low));


    if ((new_val->low >= old_val->low) &&
        (new_val->high == old_val->high)) {
        DEBUGMSGTL(("9:c64:check_wrap", "no wrap\n"));
        return 0;
    }


    if (new_val->high == old_val->high) {
        DEBUGMSGTL(("c64:check_wrap", "32 bit wrap\n"));
        if (adjust) {
            ++new_val->high;
#if SIZEOF_LONG != 4
            new_val->high &= 0xffffffff;
#endif
        }
        return 32;
    }
    else if ((new_val->high == (old_val->high + 1)) ||
             ((0 == new_val->high) && (0xffffffff == old_val->high))) {
        DEBUGMSGTL(("c64:check_wrap", "64 bit wrap\n"));
        return 64;
    }

    return -2;
}
