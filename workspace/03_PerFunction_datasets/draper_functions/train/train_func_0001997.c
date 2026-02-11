do_mget_cmd (char *args, GtkWidget *dialog)
{
	char *text, *start, *end;
	int token, n;

	GtkWidget *main_window = gtk_object_get_data(GTK_OBJECT(dialog), "image_window");
	struct camera_t *camera = camera_find(main_window, CAMERA_MAIN);
	if(! camera) {
		err_printf("no camera connected\n");
		return OBS_CMD_ERROR;
	}


	text = args;
	next_token(NULL, NULL, NULL);
	token = next_token(&text, &start, &end);
	if (token == TOK_NUMBER) {
		n = strtol(start, NULL, 10);
		d3_printf("do_mget_cmd: setting frame count to %d\n", n);
		named_spin_set(dialog, "img_number_spin", 1.0 * n);
	}
	set_named_checkb_val(dialog, "img_get_multiple_button", 1);
	set_named_checkb_val(dialog, "img_dark_checkb", 0);
	if (capture_image(dialog)) {
		err_printf("Failed to capture frame\n");
		return OBS_CMD_ERROR;
	}
	INDI_set_callback(INDI_COMMON (camera), CAMERA_CALLBACK_EXPOSE, obs_list_cmd_done, dialog);
	return OBS_CMD_RUNNING;
}
