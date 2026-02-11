mod_reopen(void)
{
logfile_t	*curr;

    RDLOCK_CL;
    curr = logfiles;
    while(curr) {
	if ( curr->path ) my_xlog(OOPS_LOG_NOTICE|OOPS_LOG_DBG|OOPS_LOG_INFORM, "mod_reopen(): Reopen %s\n", curr->path);
	if ( curr->file ) fclose(curr->file);
	if ( curr->path ) curr->file = fopen(curr->path, "a");
	if ( curr->file ) setbuf(curr->file, NULL);
	curr = curr->next;
    }
    UNLOCK_CL;
    return(MOD_CODE_OK);
}
