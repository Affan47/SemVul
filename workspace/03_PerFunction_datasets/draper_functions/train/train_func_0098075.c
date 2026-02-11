updateFont()
{
	PangoFontDescription *desc = NULL;
	gFont *fnt;

	fnt = parent->textFont();
	if (!fnt)
		fnt = parent->font();

	if (fnt)
		desc = fnt->desc();

	gtk_widget_modify_font(widget, desc);
	gtk_widget_modify_font(label, desc);
}
