rx_match(struct info *info,
                              struct value *rx, struct value *s) {
    struct value *result = NULL;
    const char *str = s->string->str;
    struct re_registers regs;
    int r;

    MEMZERO(&regs, 1);
    r = regexp_match(rx->regexp, str, strlen(str), 0, &regs);
    if (r < -1) {
        result =
            make_exn_value(ref(info), "regexp match failed (internal error)");
    } else {
        char *match = NULL;
        if (r == -1) {

            match = strdup("");
        } else {
            match = strndup(str + regs.start[0], regs.end[0] - regs.start[0]);
        }
        if (match == NULL) {
            result = info->error->exn;
        } else {
            result = make_value(V_STRING, ref(info));
            result->string = make_string(match);
        }
    }
    return result;
}
