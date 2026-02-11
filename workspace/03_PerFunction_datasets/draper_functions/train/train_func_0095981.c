logging_pause_resume(void)
{
    if(LoggingFile == NULL) {
	return;
    }
    if(Logging == TRUE) {
	Logging = FALSE;
    } else {
	Logging = TRUE;
    }
    toggle_logging_pause_resume(Logging);
}
