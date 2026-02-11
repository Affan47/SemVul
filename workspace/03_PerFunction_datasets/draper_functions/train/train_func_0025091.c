libbdplus_m2ts_close(BD_BDPLUS_ST **p)
{
    int result = -1;
    if (p && *p) {
        if ((*p)->lib && (*p)->st) {
            result = (*p)->lib->m2ts_close((*p)->st);
        }
        X_FREE(*p);
    }

    return result;
}
