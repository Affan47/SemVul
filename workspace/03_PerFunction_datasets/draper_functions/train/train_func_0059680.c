bgColorChanged(void)
{
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(m_bgcolorSelector),
								&m_currentBGColor);
	UT_RGBColor * rgbcolor = UT_UnixGdkColorToRGBColor(m_currentBGColor);
	UT_HashColor hash_color;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(m_checkTransparency), FALSE);
	m_currentBGColorTransparent = false;

	addOrReplaceVecProp("bgcolor", hash_color.setColor(*rgbcolor) + 1);
	delete rgbcolor;
	updatePreview();
}
