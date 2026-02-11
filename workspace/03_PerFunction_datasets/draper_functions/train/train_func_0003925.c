radio_menu_item_look(Glyph* g, TelltaleState* t) const {
    MonoKitImpl& i = *impl_;
    const LayoutKit& layout = *i.layout_;
    const MonoKitInfo& info = *i.info_;
    Coord box_size = font()->width('m') * info.radio_scale();
    Glyph* diamond = new Bevel(
	layout.center(layout.fixed_span(nil, box_size, box_size), 0.0, 0.0),
	&Bevel::diamond, info.dark(), info.dull(), info.light(),
	info.thickness(), false, false
    );
    return i.make_menu_item(t, diamond, g);
}
