__archive_check_magic(struct archive *a, unsigned int magic,
    unsigned int state, const char *function)
{
    if (a->magic != magic) {
        errmsg("INTERNAL ERROR: Function ");
        errmsg(function);
        errmsg(" invoked with invalid struct archive structure.\n");
        diediedie();
    }

    if (state == ARCHIVE_STATE_ANY)
        return;

    if ((a->state & state) == 0) {
        errmsg("INTERNAL ERROR: Function '");
        errmsg(function);
        errmsg("' invoked with archive structure in state '");
        write_all_states(a->state);
        errmsg("', should be in state '");
        write_all_states(state);
        errmsg("'\n");
        diediedie();
    }
}
