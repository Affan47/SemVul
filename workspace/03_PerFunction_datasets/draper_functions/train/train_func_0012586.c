request(
    GlyphIndex count, const Requisition* request, Requisition& result
) {
    Coord natural_lead = 0;
    Coord min_lead = -fil;
    Coord max_lead = fil;
    Coord natural_trail = 0;
    Coord min_trail = -fil;
    Coord max_trail = fil;
    for (int index = 0; index < count; ++index) {
        const Requirement& r = request[index].requirement(dimension_);
        if (r.defined()) {
	    Coord r_nat = r.natural();
	    Coord r_max = r_nat + r.stretch();
	    Coord r_min = r_nat - r.shrink();
	    Coord r_align = r.alignment();
	    Coord r_inv_align = 1.0 - r_align;
            natural_lead = Math::max(natural_lead, Coord(r_nat * r_align));
            max_lead = Math::min(max_lead, Coord(r_max * r_align));
            min_lead = Math::max(min_lead, Coord(r_min * r_align));
            natural_trail = Math::max(
                natural_trail, Coord(r_nat * r_inv_align)
            );
            max_trail = Math::min(max_trail, Coord(r_max * r_inv_align));
            min_trail = Math::max(min_trail, Coord(r_min * r_inv_align));
        }
    }
    Requirement r(
	natural_lead, max_lead, min_lead,
	natural_trail, max_trail, min_trail
    );
    result.require(dimension_, r);
}
