all_parse_config(cmd_parms *cmd, const char *require_line,
                                    const void **parsed_require_line)
{


    if (strcasecmp(require_line, "granted") == 0) {
        *parsed_require_line = (void *)1;
        return NULL;
    }
    else if (strcasecmp(require_line, "denied") == 0) {

        return NULL;
    }
    else {
        return "Argument for 'Require all' must be 'granted' or 'denied'";
    }
}
