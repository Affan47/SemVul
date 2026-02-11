renderText(GLETextDO* text, GLEPropertyStore* prop) {
	GLESaveRestore saved_state;
	g_select_device(GLE_DEVICE_EPS);
	PSGLEDevice* dev = (PSGLEDevice*)g_get_device_ptr();
	dev->startRecording();
	saved_state.save();
	g_clear();
	g_resetfont();
	g_scale(PS_POINTS_PER_INCH/CM_PER_INCH, PS_POINTS_PER_INCH/CM_PER_INCH);
	g_translate(1.0*CM_PER_INCH/72, 1.0*CM_PER_INCH/72);
	dev->startRecording();

	GLEColor* color = prop->getColorProperty(GLEDOPropertyColor);
	g_set_color(color);

	double hei = prop->getRealProperty(GLEDOPropertyFontSize);
	g_set_hei(hei);
	g_set_font_width(-1);
	g_set_line_style("1");
	g_set_line_width(0.02);

	GLEFont* font = prop->getFontProperty(GLEDOPropertyFont);
	if (font == NULL) {
		font = getFont("rm");
	}
	g_set_font(font->getIndex());
	char* str = (char*)text->getTextC();

	double x1, x2, y1, y2;
	g_measure(str, &x1, &x2, &y2, &y1);
	text->initBB(x2-x1, y2-y1, -y1);


	g_move(0.0, 0.0);
	g_jtext(JUST_BL);

	dev->getRecordedBytes(text->getPostScriptPtr());


	saved_state.restore();
}
