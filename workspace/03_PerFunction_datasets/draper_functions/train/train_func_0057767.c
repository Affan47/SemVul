compute_tile_request(
    DimensionName d, float a, GlyphIndex count, const Requisition* request,
    Requisition& result
) {
    Coord natural = 0, min_size = 0, max_size = 0;
    for (GlyphIndex i = 0; i < count; i++) {
        const Requirement& r = request[i].requirement(d);
        if (r.defined()) {
	    Coord n = r.natural();
	    natural += n;
	    max_size += n + r.stretch();
	    min_size += n - r.shrink();
	}
    }
    Requirement& nr = result.requirement(d);
    nr.natural(natural);
    nr.stretch(max_size - natural);
    nr.shrink(natural - min_size);
    nr.alignment(a);
}
