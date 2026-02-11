PG_Label(PG_Widget* parent, const PG_Rect& r, const std::string& text, const std::string& style) :
		PG_Widget(parent, r),
my_indent(0) {

	my_alignment = LEFT;
	my_srfIcon = NULL;
	my_freeicon = false;

	SetText(text);
	LoadThemeStyle(style);
}
