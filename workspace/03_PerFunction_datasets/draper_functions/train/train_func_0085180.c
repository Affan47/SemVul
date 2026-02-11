open_man_file(gchar *manfile)
{
	GtkWidget *statusbar,*text;
	GtkTextBuffer *tb;
	gzFile *f;
	gint bytes_read;
	int n;
	char extension[10];
	gchar *utf8;
	gchar * buffer = (gchar*)malloc(BUFFER_SIZE);


	text=lookup_widget(GTK_WIDGET(wprincipal),"text");
	tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text));
	gtk_text_buffer_set_text (tb, "", 0);


	statusbar=lookup_widget(GTK_WIDGET(wprincipal),"statusbar1");
	gtk_statusbar_pop(GTK_STATUSBAR(statusbar),1);
	gtk_statusbar_push(GTK_STATUSBAR(statusbar),1,_("File opened."));


	n = strlen(manfile)-3;
	strncpy(extension,manfile+n,3);
	if (!strncmp(extension,".gz",3))
	    in_gzip=1;
	else
	    in_gzip=0;


	if ((f=gzopen((gchar *)manfile,"rb"))!=NULL)
	{
	  while(!gzeof(f))
	  {
		bytes_read=gzread(f,buffer,BUFFER_SIZE);
		if (bytes_read>0)
		{
			utf8 = NULL;
			if (g_utf8_validate(buffer, -1, NULL) == FALSE)
			{
				utf8 = g_locale_to_utf8(buffer, -1, NULL, NULL, NULL);
			}
			if (utf8 != NULL){
				strncpy(buffer,utf8, BUFFER_SIZE - 1);
				buffer[BUFFER_SIZE - 1] = 0;
			}
			gtk_text_buffer_insert_at_cursor(tb, buffer ,bytes_read);
		}
	  }
  	  gzclose(f);
	}
	else
		mensaje(strerror(errno),GTK_MESSAGE_ERROR);
	if (open_file) gtk_widget_destroy (open_file);
}
