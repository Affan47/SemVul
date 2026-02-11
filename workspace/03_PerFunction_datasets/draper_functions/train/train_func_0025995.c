addoptions(qaconf_t *qaconf, const qaconf_option_t *options) {
    if (qaconf == NULL || options == NULL) {
        _seterrmsg(qaconf, "Invalid parameters.");
        return -1;
    }


    uint32_t numopts;
    for (numopts = 0; options[numopts].name != NULL; numopts++)
        ;
    if (numopts == 0)
        return 0;


    size_t newsize = sizeof(qaconf_option_t) * (qaconf->numoptions + numopts);
    qaconf->options = (qaconf_option_t *) realloc(qaconf->options, newsize);
    memcpy(&qaconf->options[qaconf->numoptions], options,
           sizeof(qaconf_option_t) * numopts);
    qaconf->numoptions += numopts;

    return numopts;
}
