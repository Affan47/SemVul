parse_range(char *range, ARTNUM *low, ARTNUM *high)
{
    char *hyphen, *end;

    *low = 0;
    *high = 0;
    hyphen = strchr(range, '-');
    if (hyphen == NULL) {
        *low = strtoul(range, &end, 10);
        if (*low == 0 || *end != '\0')
            return false;
        *high = *low;
        return true;
    } else {
        *hyphen = '\0';
        if (*range != '\0') {
            *low = strtoul(range, &end, 10);
            if (*low == 0 || *end != '\0')
                return false;
        }
        if (hyphen[1] != '\0') {
            *high = strtoul(hyphen + 1, &end, 10);
            if (*high == 0 || *end != '\0')
                return false;
        }
        *hyphen = '-';
        return true;
    }
}
