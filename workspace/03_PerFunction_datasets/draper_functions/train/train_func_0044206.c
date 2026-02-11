spiftool_join(spif_charptr_t sep, spif_charptr_t *slist)
{
    register unsigned long i;
    size_t len, slen;
    spif_charptr_t new_str;

    ASSERT_RVAL(slist != SPIF_NULL_TYPE(ptr), SPIF_NULL_TYPE(ptr));
    REQUIRE_RVAL(*slist != SPIF_NULL_TYPE(ptr), SPIF_NULL_TYPE(ptr));
    if (sep == NULL) {
        sep = SPIF_CHARPTR("");
    }
    slen = strlen(SPIF_CHARPTR_C(sep));
    for (i = len = 0; slist[i]; i++) {
        len += strlen(SPIF_CHARPTR_C(slist[i]));
    }
    len += slen * (i - 1);
    new_str = SPIF_CAST(charptr) MALLOC(len);
    strcpy(SPIF_CHARPTR_C(new_str), SPIF_CHARPTR_C(slist[0]));
    for (i = 1; slist[i]; i++) {
        if (slen) {
            strcat(SPIF_CHARPTR_C(new_str), SPIF_CHARPTR_C(sep));
        }
        strcat(SPIF_CHARPTR_C(new_str), SPIF_CHARPTR_C(slist[i]));
    }
    return new_str;
}
