set_label (gchar * str)
{
	if (str)
		std::strcpy (text, str);
	else
		text[0]='\0';
	if (layout)
		pango_layout_set_text(layout,text,-1);
	else
		layout=gtk_widget_create_pango_layout (draw_area, text);
	draw ();
}
