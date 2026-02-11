do_decode(ARTICLE **arts, int no_parts)
{
    char	message[128];
    FILE	*fp;
    char	*file_name;
    pid_t	pid;
    long	result[2];

    fp = create_temp_file(&file_name);
    if (!fp) {
	set_message("Failed to create temp file!", True);
	return False;
    }
    unlink(file_name);

    strcpy(message, "Saving to temp file...   ");
    set_busy(True);
    if (save_to_file(fp, message, arts, no_parts, SAVE_BODY, result) < 0) {
	reconnect_server(True);
	unset_busy();
	return False;
    }
    unset_busy();

    if (result[0] < 0) {
	set_message("Error with temp file!", True);
	fclose(fp);
	return False;
    }

    pid = fork_nicely(XtNewString("uudecode"), pipe_context_callback,
		      global.stderr_timeout >= 0);
    if (pid < 0) {
	fclose(fp);
	set_message("Failed to start 'uudecode' program!", True);
	return False;
    }

    if (pid == 0)
	uudecode_child(fileno(fp));

    fclose(fp);
    set_message("Started uudecode program.", False);
    return True;
}
