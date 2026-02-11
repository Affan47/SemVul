handle_fakeuser(char *username)
{
    char *data[5];
    int num_parms = 0, i, funum;
    char *buf;

    show_top();

    num_parms = get_parms(username);
    num_parms++;

    if (prog_config.config_bits3 & SHOW_FAKEUSER) {
	if (num_parms > 5) {
	    printf("\n                    Sorry, you specified too many options.\n\n");
	    fflush(stdout);
	    show_bottom();
	    mylog(LOG_WARN, "Too many options specified in fake user finger", NULL);
	    return;
 	}


	for (i = 0; i < 5; i++)
	    data[i] = NULL;


	for (i = 0; i < num_parms; i++)
	    data[i] = (char *) malloc(strlen(username)+1);

	if (num_parms == 1)
	    sscanf(username, "%[^\r\n]\r\n", data[0]);
	else if (num_parms == 2)
	    sscanf(username, "%[^.].%[^\r\n]\r\n", data[0], data[1]);
	else if (num_parms == 3)
	    sscanf(username, "%[^.].%[^.].%[^\r\n]\r\n", data[0], data[1], data[2]);
	else if (num_parms == 4)
	    sscanf(username, "%[^.].%[^.].%[^.].%[^\r\n]\r\n",
		data[0], data[1], data[2], data[3]);
	else if (num_parms == 5)
	    sscanf(username, "%[^.].%[^.].%[^.].%[^.].%[^\r\n]\r\n",
		data[0], data[1], data[2], data[3], data[4]);

	mylog(LOG_USER, "Fakeuser: ", username);

	funum = search_fake_pos(data[0]);


	if (funum != -1) {
	    char send_string[80];

	    if (prog_config.fusers[funum].searchable)
		snprintf(send_string, sizeof(send_string), "%s %s %s %s %s",
		    prog_config.fusers[funum].script,
		    (data[1] != NULL) ? data[1] : "",
		    (data[2] != NULL) ? data[2] : "",
		    (data[3] != NULL) ? data[3] : "",
		    (data[4] != NULL) ? data[4] : "");
	    else
		snprintf(send_string, sizeof(send_string), "%s", prog_config.fusers[funum].script);

	    if ((buf = safe_exec(NOBODY_UID, NOBODY_GID, send_string)) != NULL) {
		printf ("%s", buf);
		fflush (stdout);
		free (buf);
	    }
	}
    } else {
	printf("\n");
	printf("             Sorry, this system does not have any fake users enabled!\n\n");
	mylog(LOG_WARN, "Fake user requested, but rejected - disabled.", " ");
    }

    show_bottom();
}
