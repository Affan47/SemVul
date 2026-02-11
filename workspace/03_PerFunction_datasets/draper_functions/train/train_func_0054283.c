uidline_matches_string(const gchar *file_line,
				       uid_t user_id) {


    gchar *uidstr;
    uid_t this_uid;
    size_t i;
    size_t uid_offset = 5;

    size_t number_of_tabs_found = 0;
    size_t line_length;
    size_t tab_locations[4];


    line_length = strlen(file_line);

    for (i = 0; i <= line_length; i++) {
	if (file_line[i] == '\t') {
	    tab_locations[number_of_tabs_found] = i;
	    ++number_of_tabs_found;


	    if (number_of_tabs_found >= 4) {
		break;
	    }
	}
    }

    if (number_of_tabs_found != 4) {
	return FALSE;
    }


    uidstr = calloc(tab_locations[1] - uid_offset + 1, sizeof(gchar));
    uidstr = strncpy(uidstr, file_line + uid_offset, tab_locations[1] - uid_offset);

    uidstr[tab_locations[1] - uid_offset] = '\0';
    this_uid = atoi(uidstr);

    free(uidstr);
    if (this_uid == user_id) {
	return TRUE;
    } else {
	return FALSE;
    }
}
