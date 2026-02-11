rate(int rating) {
	if(playfork) {
		struct hash p = { 0, NULL };
		const char * method, * error;
		char * response, full_method[32];

		switch(rating) {
			case RATING_LOVE:
				method = "love";
				break;

			case RATING_BAN:
				kill(playfork, SIGUSR1);
				enable(INTERRUPTED);
				method = "ban";
				break;

			case RATING_UNLOVE:
				method = "unlove";
				break;

			case RATING_UNBAN:
				method = "unban";
				break;

			default:
				return 0;
		}

		set(& p, "track", value(& track, "title"));
		set(& p, "artist", value(& track, "creator"));

		snprintf(full_method, sizeof(full_method), "track.%s", method);

		response = rest(full_method, & p);
		if(!response)
			return 0;

		error = error_message(response);

		free(response);
		empty(& p);

		if(error != NULL) {
			fprintf(stderr, "Failed to %s track. %s.\n", method, error);
		}
		else {
			char * rating_code[RATING_MAX];

			rating_code[RATING_LOVE] = "L";
			rating_code[RATING_BAN] = "B";
			rating_code[RATING_UNLOVE] = "U";
			rating_code[RATING_UNBAN] = "X";

			rate_command(rating_code[rating]);

			return 1;
		}
	}

	return 0;
}
