extract_varname (char *targ, const char *src, int *len)
{
    int err = 0;

    *targ = '\0';
    *len = gretl_namechar_spn(src);

    if (*len >= VNAMELEN) {

	err = E_UNKVAR;
    } else {
	strncat(targ, src, *len);
    }

    return err;
}
