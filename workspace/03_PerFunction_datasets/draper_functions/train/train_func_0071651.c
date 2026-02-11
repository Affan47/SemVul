crm_get_interval(const char *input)
{
    crm_time_t *interval = NULL;
    unsigned long long msec = 0;

    if (input == NULL) {
        return 0;

    } else if (input[0] != 'P') {
        return crm_get_msec(input);
    }

    interval = crm_time_parse_duration(input);
    msec = crm_time_get_seconds(interval);
    crm_time_free(interval);
    return msec * 1000;
}
