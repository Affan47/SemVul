jk_parse_sysprops(jk_pool_t *p, const char *sysprops)
{
    char **rc = NULL;
#ifdef _MT_CODE_PTHREAD
    char *lasts;
#endif

    if (p && sysprops) {
        char *prps = jk_pool_strdup(p, sysprops);
        if (prps && strlen(prps)) {
            unsigned num_of_prps;

            for (num_of_prps = 1; *sysprops; sysprops++) {
                if ('*' == *sysprops) {
                    num_of_prps++;
                }
            }

            rc = jk_pool_alloc(p, (num_of_prps + 1) * sizeof(char *));
            if (rc) {
                unsigned i = 0;
#ifdef _MT_CODE_PTHREAD
                char *tmp = strtok_r(prps, "*", &lasts);
#else
                char *tmp = strtok(prps, "*");
#endif

                while (tmp && i < num_of_prps) {
                    rc[i] = tmp;
#ifdef _MT_CODE_PTHREAD
                    tmp = strtok_r(NULL, "*", &lasts);
#else
                    tmp = strtok(NULL, "*");
#endif
                    i++;
                }
                rc[i] = NULL;
            }
        }
    }

    return rc;
}
