draw(Canvas* c, const Allocation& a) const {
    if (c->damaged(extension_)) {
	MonoGlyph::draw(c, a);
    }
}
