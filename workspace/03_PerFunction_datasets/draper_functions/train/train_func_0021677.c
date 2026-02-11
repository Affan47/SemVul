krb5_os_localaddr_profile (krb5_context context, struct localaddr_data *datap)
{
    krb5_error_code err;
    static const char *const profile_name[] = {
        KRB5_CONF_LIBDEFAULTS, KRB5_CONF_EXTRA_ADDRESSES, 0
    };
    char **values;
    char **iter;
    krb5_address **newaddrs;

#ifdef DEBUG
    fprintf (stderr, "looking up extra_addresses foo\n");
#endif

    err = profile_get_values (context->profile, profile_name, &values);

    if (err)
        return 0;

    for (iter = values; *iter; iter++) {
        char *cp = *iter, *next, *current;
        int i, count;

#ifdef DEBUG
        fprintf (stderr, "  found line: '%s'\n", cp);
#endif

        for (cp = *iter, next = 0; *cp; cp = next) {
            while (isspace ((int) *cp) || *cp == ',')
                cp++;
            if (*cp == 0)
                break;

#ifdef DEBUG
            fprintf (stderr, "    addr found in '%s'\n", cp);
#endif
            current = cp;
            while (*cp != 0 && !isspace((int) *cp) && *cp != ',')
                cp++;
            if (*cp != 0) {
                next = cp + 1;
                *cp = 0;
            } else
                next = cp;

#ifdef DEBUG
            fprintf (stderr, "    processing '%s'\n", current);
#endif
            newaddrs = 0;
            err = k5_os_hostaddr (context, current, &newaddrs);
            if (err)
                continue;
            for (i = 0; newaddrs[i]; i++) {
#ifdef DEBUG
                fprintf (stderr, "    %d: family %d", i,
                         newaddrs[i]->addrtype);
                fprintf (stderr, "\n");
#endif
            }
            count = i;
#ifdef DEBUG
            fprintf (stderr, "    %d addresses\n", count);
#endif
            if (datap->cur_idx + count >= datap->cur_size) {
                krb5_address **bigger;
                bigger = realloc (datap->addr_temp,
                                  sizeof (krb5_address *) * (datap->cur_idx + count));
                if (bigger) {
                    datap->addr_temp = bigger;
                    datap->cur_size = datap->cur_idx + count;
                }
            }
            for (i = 0; i < count; i++) {
                if (datap->cur_idx < datap->cur_size)
                    datap->addr_temp[datap->cur_idx++] = newaddrs[i];
                else
                    free (newaddrs[i]->contents), free (newaddrs[i]);
            }
            free (newaddrs);
        }
    }
    return 0;
}
