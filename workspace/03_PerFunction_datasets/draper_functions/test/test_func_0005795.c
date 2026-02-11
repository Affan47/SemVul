partial_dialogue_callback(Widget w,
				      XtPointer client_data,
				      XtPointer call_data)
{
    NoticeReply	reply = (NoticeReply)call_data;
    PCE		*c = (PCE *)client_data;

    if (global.busy || (global.mode != NewsModeThread &&
			global.mode != NewsModeGroup))
	return;

    if (reply == NoticeReplyLeft) {
	SERVER	*server;
	char	*buffer;
	FILE	*fp;

	fp = create_temp_file(&buffer);
	if (!fp) {
	    set_message("Failed to create temp file!", True);
	    return;
	}
	unlink(buffer);

	set_busy(True);
	buffer = snarf_articles(fp, c->arts + 1, c->tot);
	if (!buffer) {
	    fclose(fp);
	    reconnect_server(True);
	    unset_busy();
	    return;
	}

	unset_busy();

	if (atoi(buffer) != NNTP_OK_ARTICLE) {
	    char	message[256];

	    if (strlen(buffer) > 128)
		buffer[128] = '\0';
	    sprintf(message,
		    "Couldn't get all parts, message from server is: %s",
		    buffer);
	    set_message(message, True);
	    fclose(fp);
	    return;
	}

	if (fflush(fp) != 0 || fseek(fp, SEEK_SET, 0) != 0) {
	    perror("knews: fseek");
	    set_message("Error: couldn't rewind temp file!", True);
	    fclose(fp);
	    return;
	}

	set_curr_art(NULL, False);

	server = server_create(fileno(fp));

	buffer = server_read(server);
	if (!res_full_header())
	    buffer = do_mime(NULL, server, buffer, False, NULL, 0, NULL);
	else {
	    XFontStruct	*font = ascii_font->header_font;
	    Pixel	pixel = global.header_pixel;

	    ArtTextClearLines(main_widgets.text);
	    ScrollableSuspend(main_widgets.text);
	    while (buffer && !IS_DOT(buffer)) {
		ArtTextAddLine(main_widgets.text, buffer, font, pixel);
		if (buffer[0] == '\0') {
		    font = ascii_font->body_font;
		    pixel = global.pixel;
		}
		buffer = server_read(server);
	    }
	    ScrollableResume(main_widgets.text);
	}

	if (!buffer)
	    set_message("Error with temp file!", True);
	else
	    set_standard_message();

	fclose(fp);
	server_set_fd(server, -1);
	server_free(server);
    }

    XtPopdown(c->notice);
    XtDestroyWidget(c->notice);
    c->notice = NULL;
    remove_cache_entry(c);
}
