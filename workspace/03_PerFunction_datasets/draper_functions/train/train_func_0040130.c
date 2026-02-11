cmd_transform(struct command *cmd) {
    const char *lens = arg_value(cmd, "lens");
    const char *filter = arg_value(cmd, "filter");
    const char *file = arg_value(cmd, "file");
    int r, excl = 0;

    if (STREQ("excl", filter))
        excl = 1;
    else if (STREQ("incl", filter))
        excl = 0;
    else
        ERR_REPORT(cmd, AUG_ECMDRUN,
                   "FILTER must be \"incl\" or \"excl\"");

    r = aug_transform(cmd->aug, lens, file, excl);
    if (r < 0)
        ERR_REPORT(cmd, AUG_ECMDRUN,
                   "Adding transform for %s on lens %s failed", lens, file);
}
