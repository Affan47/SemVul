do_query_glyphs(const OpenType::Font &otf, ErrorHandler *errh, ErrorHandler *result_errh)
{
    int before_nerrors = errh->nerrors();
    try {

	Cff cff(otf.table("CFF"), errh);
	if (!cff.ok())
	    throw OpenType::Error();

	Cff::FontParent *fp = cff.font(PermString(), errh);
	if (!fp || !fp->ok())
	    throw OpenType::Error();
	Cff::Font *font = dynamic_cast<Cff::Font *>(fp);
	if (!font) {
	    errh->error("CID-keyed fonts not supported");
	    throw OpenType::Error();
	}


	Vector<PermString> glyph_names;
	font->glyph_names(glyph_names);
	for (PermString* s = glyph_names.begin(); s < glyph_names.end(); s++)
	    result_errh->message("%s", s->c_str());
    } catch (OpenType::Error) {
	if (errh->nerrors() == before_nerrors)
	    result_errh->message("no glyph name information");
    }
}
