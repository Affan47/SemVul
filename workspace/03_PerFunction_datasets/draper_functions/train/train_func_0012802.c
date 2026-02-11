cmd_sel(struct unqueue_data *unqd)
{
	GtkWidget *fsw;
	char	*pr = gprompt(1676);
	GString	*labp = g_string_new(NULL);
	const  char  *dirn, *filen;

	fsw = gtk_file_selection_new(pr);
	free(pr);

	dirn = gtk_label_get_text(GTK_LABEL(unqd->dirsw));
	filen = gtk_label_get_text(GTK_LABEL(unqd->cfw));
	if  (strlen(dirn) <= 1)
		g_string_printf(labp, "%s%s", dirn, filen);
	else
		g_string_printf(labp, "%s/%s", dirn, filen);
	gtk_file_selection_set_filename(GTK_FILE_SELECTION(fsw), labp->str);
	g_string_free(labp, TRUE);
	gtk_file_selection_hide_fileop_buttons(GTK_FILE_SELECTION(fsw));

	while  (gtk_dialog_run(GTK_DIALOG(fsw)) == GTK_RESPONSE_OK)  {
		const char *newfile = gtk_file_selection_get_filename(GTK_FILE_SELECTION(fsw));
		const char *sp = strrchr(newfile, '/');
		if  (!sp)  {
			doerror(319);
			continue;
		}
		if  (strlen(sp) <= 1)  {
			doerror(321);
			continue;
		}
		if  (newfile == sp)
			gtk_label_set_text(GTK_LABEL(unqd->dirsw), "/");
		else  {
			char	*newd = malloc(sp - newfile + 1);
			if  (!newd)
				nomem();
			strncpy(newd, newfile, sp-newfile);
			newd[sp-newfile] = '\0';
			gtk_label_set_text(GTK_LABEL(unqd->dirsw), newd);
			free(newd);
		}
		gtk_label_set_text(GTK_LABEL(unqd->cfw), sp+1);
		break;
	}
	gtk_widget_destroy(fsw);
}
