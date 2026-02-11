make_mover(TelltaleState* t, Beveler b) {
    const MFKitInfo& i = *info_;
    Coord m = 2.0;
    Glyph* enabled = layout_->margin(
	new Bevel(nil, b, i.light(), i.flat(), i.dark(), i.thickness()), m
    );
    Glyph* active = layout_->margin(
	new Bevel(nil, b, i.dark(), i.flat(), i.light(), i.thickness()), m
    );
    Glyph* disabled = new MFKitForeground(enabled, i.gray_out());
    return new ChoiceItem(
	t, disabled, enabled, enabled, active, active,
	enabled, active, active, active, disabled
    );
}
