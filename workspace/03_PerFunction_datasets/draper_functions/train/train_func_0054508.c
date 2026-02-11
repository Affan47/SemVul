modperl_env_hv_delete(pTHX_ HV *hv, char *key)
{
    I32 klen = strlen(key);
    if (hv_exists(hv, key, klen)) {
        (void)hv_delete(hv, key, strlen(key), G_DISCARD);
    }
}
