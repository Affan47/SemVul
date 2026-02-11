apply(const Vector<Substitution>& sv, bool allow_single, int lookup, const GlyphFilter& glyph_filter, const Vector<PermString>& glyph_names)
{
    Vector<Glyph> glyphs;
    Vector<Code> codes;


    ChangedContext ctx(_encoding.size());


    int failures = 0;
    for (const Substitution *s = sv.begin(); s != sv.end(); s++) {
	bool is_single = s->is_single() || s->is_alternate();
	bool is_apply_single = is_single && allow_single;
	bool is_apply_simple_context_ligature = !is_single && !s->is_multiple() && s->is_simple_context();

	if (is_apply_single || is_apply_simple_context_ligature) {
	    s->all_in_glyphs(glyphs);
	    for (codes.clear(); next_encoding(codes, glyphs); ) {
		if (is_apply_single)
		    apply_single(codes[0], s, lookup, ctx, glyph_filter, glyph_names);
		else
		    apply_simple_context_ligature(codes, s, lookup, ctx);
	    }
	} else
	    failures++;
    }

    return sv.size() - failures;
}
