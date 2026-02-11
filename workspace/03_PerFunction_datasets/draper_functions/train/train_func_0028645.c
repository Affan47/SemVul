uish_init(struct uish_s * uish, const char * self, const char * prompt, FILE * config) {
    int optchar = -1;

    if (NULL == uish)
        goto return_err;

    memset(uish, 0, sizeof(struct uish_s));
    local_uish = uish;

    uish->prompt = strdup(prompt);
    if (NULL == uish->prompt)
        goto return_err;


    uish->hist = setup_history();
    if (NULL == uish->hist)
        goto return_err;

    uish->el = setup_el(self);
    if (NULL == uish->el)
        goto return_err;

    uish->tok = setup_tok(NULL);
    if (NULL == uish->tok)
        goto return_err;

    uish->completion_tok = setup_tok(NULL);
    if (NULL == uish->completion_tok)
        goto return_err;

    list_init(&uish->commands, NULL);
    if (config != NULL) {
        if (SCAN_ERR == lexscan(config, uish)) {
            DBG(0, "error while parsing config\n");
            goto return_err;
        }
    } else
        goto return_err;

    return 1;
return_err:
    return 0;
}
