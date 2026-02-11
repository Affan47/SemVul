copy_to_clipboard_without_background()
{
	glarea_rafresh(GLArea);
	guchar color[3];
	gint numCol = get_background_color(color);
	while( gtk_events_pending() ) gtk_main_iteration();
	if(numCol>-1) gabedit_save_image_gl(GLArea, NULL, NULL,color);
	else gabedit_save_image_gl(GLArea, NULL, NULL,NULL);
}
