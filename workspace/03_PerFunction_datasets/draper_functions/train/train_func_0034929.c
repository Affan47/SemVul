pathinclude(const char *dir)
{
    register Dir_t *dp;

    if (dir && *dir && !streq(dir, ".")) {
	if (!(dp = oldof(0, Dir_t, 1, strlen(dir))))
	    return -1;
	strcpy(dp->dir, dir);
	if (state.tail)
	    state.tail = state.tail->next = dp;
	else
	    state.head = state.tail = dp;
    }
    return 0;
}
