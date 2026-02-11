init_encryption_keys(const char *pw, struct zc_key *k)
{
    int i = 0;
    set_default_encryption_keys(k);
    while (pw[i] != '\0') {
        update_keys(pw[i], k, k);
        ++i;
    }
}
