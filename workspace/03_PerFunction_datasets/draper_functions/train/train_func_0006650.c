ruv_has_csns(const RUV *ruv)
{
        PRBool retval = PR_TRUE;
        CSN *mincsn = NULL;
        CSN *maxcsn = NULL;

        ruv_get_min_csn(ruv, &mincsn);
        ruv_get_max_csn(ruv, &maxcsn);
        if (mincsn) {
                csn_free(&mincsn);
                csn_free(&maxcsn);
        } else if (maxcsn) {
                csn_free(&maxcsn);
        } else {
                retval = PR_FALSE;
        }

        return retval;
}
