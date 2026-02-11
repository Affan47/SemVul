set_label (gchar * str_w, gchar * str_m)
{
	strcpy (text_w, str_w);
	if (str_m)
		strcpy (text_m, str_m);
	else
		text_m[0]='\0';

	if (layout_w)
		pango_layout_set_text(layout_w,text_w,-1);
	else
	{
		layout_w=gtk_widget_create_pango_layout (draw_area, text_w);
		pango_layout_set_font_description(layout_w,Skin->reciteword.n_font);
	}
	if (layout_m)
		pango_layout_set_text(layout_m,text_m,-1);
	else
		layout_m=gtk_widget_create_pango_layout (draw_area, text_m);

	draw ();
}
