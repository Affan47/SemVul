cmd_rename(struct command *cmd) {
    const char *src = arg_value(cmd, "src");
    const char *lbl = arg_value(cmd, "lbl");
    int cnt;

    cnt = aug_rename(cmd->aug, src, lbl);
    if (cnt < 0)
        ERR_REPORT(cmd, AUG_ECMDRUN,
                   "Renaming %s to %s failed", src, lbl);
    if (! HAS_ERR(cmd))
        fprintf(cmd->out, "rename : %s to %s %d\n", src, lbl, cnt);
}
