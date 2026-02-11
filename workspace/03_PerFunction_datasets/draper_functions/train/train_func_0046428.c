FCEUI_MovieToggleReadOnly()
{
	char message[260];

	if(movie_readonly)
		strcpy(message, "Movie is now Read+Write");
	else
	{
		strcpy(message, "Movie is now Read-Only");
	}

	if(movieMode == MOVIEMODE_INACTIVE)
		strcat(message, " (no movie)");
	else if (movieMode == MOVIEMODE_FINISHED)
		strcat(message, " (finished)");

	FCEU_DispMessage(message,0);
	movie_readonly = !movie_readonly;
}
