draw(Canvas* c, const Allocation& a) const {
    if (font_ != nil) {
	const Font* f = font_;
	Coord x = a.x();
	Coord y = a.y();

	c->character(
            f, fill_code_, fill_width_, kit_->bg2(), x, y + fill_height_);
	c->character(f, ul_code_, ul_width_, kit_->bg3(), x, y + ul_height_);
	c->character(f, lr_code_, lr_width_, kit_->white(), x, y + lr_height_);
    }
}
