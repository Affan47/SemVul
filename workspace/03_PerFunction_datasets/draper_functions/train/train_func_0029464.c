vi_is_blacklisted_url(struct vih *vih, char *url)
{
    unsigned int i;

    for (i = 0; i < VI_BLACKLIST_LEN; i++) {
        if (strstr(url, vi_blacklist[i])) {
            vih->blacklisted++;
            return 1;
        }
    }
    return 0;
}
