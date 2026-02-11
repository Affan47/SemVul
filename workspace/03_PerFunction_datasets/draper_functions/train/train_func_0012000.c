spiftool_condense_whitespace(spif_charptr_t s)
{

    register unsigned char gotspc = 0;
    register spif_charptr_t pbuff = s, pbuff2 = s;

    ASSERT_RVAL(s != SPIF_NULL_TYPE(ptr), SPIF_NULL_TYPE(ptr));
    D_STRINGS(("condense_whitespace(%s) called.\n", s));
    for (; *pbuff2; pbuff2++) {
        if (isspace(*pbuff2)) {
            if (!gotspc) {
                *pbuff = ' ';
                gotspc = 1;
                pbuff++;
            }
        } else {
            *pbuff = *pbuff2;
            gotspc = 0;
            pbuff++;
        }
    }
    if ((pbuff >= s) && (isspace(*(pbuff - 1))))
        pbuff--;
    *pbuff = 0;
    D_STRINGS(("condense_whitespace() returning \"%s\".\n", s));
    return (SPIF_CAST(charptr) REALLOC(s, strlen(SPIF_CHARPTR_C(s)) + 1));
}
