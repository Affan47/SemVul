pick(Canvas* c, const Allocation& a, int depth, Hit& h) {
    if (h.right() >= a.left() && h.left() < a.right() &&
	h.top() >= a.bottom() && h.bottom() < a.top()
    ) {
	BoxImpl* b = impl_;
	Extension ext;
	ext.clear();
	AllocationInfo& info = b->info(c, a, ext);
	Allocation* aa = info.component_allocations();
	GlyphIndex n = count();
	for (GlyphIndex i = 0; i < n; i++) {
	    Glyph* g = component(i);
	    if (g != nil) {
		h.begin(depth, this, i);
		g->pick(c, aa[i], depth + 1, h);
		h.end();
	    }
	}
    }
}
