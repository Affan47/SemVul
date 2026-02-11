to_scenario(const char *str) {
    int i = SCEN_COUNT;
    for (; i > 0; ) {
        i--;
        if (strcasecmp(str, scenarios[i]) == 0) return i;
    }
    return -1;
}
