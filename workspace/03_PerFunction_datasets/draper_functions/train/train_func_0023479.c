scroll_bar_look(DimensionName d, Adjustable* a) const {
    OLKitImpl& i = *impl_;
    LayoutKit& l = *LayoutKit::instance();
    Coord shaft_gap = i.specs_->shaft_gap();

    Glyph* anchor1 = i.cable_anchor(a, OL_ToLimit::start, d);
    Glyph* anchor2 = i.cable_anchor(a, OL_ToLimit::end, d);
    Glyph* scrollbar = i.scrollbar(a, d);
    Glyph* result;

    if (d == Dimension_X) {
	Glyph* vspace = l.vspace(shaft_gap);
	result = l.vbox(vspace, l.hbox(anchor1, scrollbar, anchor2), vspace);
    } else {
	Glyph* hspace = l.hspace(shaft_gap);
	result = l.hbox(hspace, l.vbox(anchor1, scrollbar, anchor2), hspace);
    }
    return result;
}
