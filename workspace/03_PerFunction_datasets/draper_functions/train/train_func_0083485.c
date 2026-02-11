add(const char* title, Glyph* glyph) {
    const LayoutKit& layout = *layout_;
    Glyph* g = layout.margin(
	glyph,
	0.0, fil, 0.0, 0.0, fil, 0.0,
	0.0, 0.25*fil, 0.0, 0.0, 0.75*fil, 0.0
    );
    if (title != nil) {
	WidgetKit& kit = *kit_;
	kit.push_style();
	kit.style(title_style_);
	g = layout.overlay(
	    layout.center(g),
	    layout.center(
		layout.margin(
		    kit.fancy_label(title),
		    0.0, fil, 0.0, 0.0, fil, 0.0,
		    0.0, 0.90*fil, 0.0, 0.0, 0.10*fil, 0.0
		)
	    )
	);
	kit.pop_style();
    }
    body_->append(
	layout.center(layout.fixed_span(g, size_, size_), 0.0, 1.0)
    );
}
