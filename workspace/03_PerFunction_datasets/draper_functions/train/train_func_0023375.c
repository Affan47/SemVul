cwd_restart(void *p)
{
    int retval = -1;
    char new_cwd[PATH_MAX+1];

    if (getcwd(new_cwd, PATH_MAX) == NULL) {
	perror("getcwd");
        goto out;
    }

    if (strncmp(checkpoint_cwd, new_cwd, sizeof(checkpoint_cwd))) {
	CRUT_FAIL("Did not restore cwd %s", checkpoint_cwd);
	retval = -1;
    } else {
	retval = 0;
    }

out:
    return retval;
}
