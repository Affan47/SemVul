set_current_line_style (GtkWidget      *widget,
			GtkSourceStyle *style)
{
	GdkColor bg;
	if (get_color (style, FALSE, &bg)) {
		gtk_scintilla_set_caret_line_back(GTK_SCINTILLA(widget), GdkColor_to_Int(bg));
	} else {
		gtk_scintilla_set_caret_line_back(GTK_SCINTILLA(widget), 13684944);
  }
}
