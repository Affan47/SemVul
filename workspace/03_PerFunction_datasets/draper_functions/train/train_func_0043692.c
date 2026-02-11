dotlessj_font(Metrics &metrics, ErrorHandler *errh, Glyph &dj_glyph)
{
    if (!_font_name || !_finfo.otf || !_finfo.cff)
	return -1;

    String dj_name;
    bool install_metrics;

    if ((dj_name = installed_metrics_font_name(_font_name, "dotlessj")))
	install_metrics = false;
    else {
	dj_name = suffix_font_name(_font_name, "--lcdfj");
	install_metrics = true;
    }


    for (int i = 0; i < metrics.n_mapped_fonts(); i++)
	if (metrics.mapped_font_name(i) == dj_name)
	    return i;

    if (String filename = installed_type1_dotlessj(_otf_file_name, _finfo.cff->font_name(), (output_flags & G_DOTLESSJ), errh)) {


	if (filename == String("\0", 1))
	    return J_NODOT;


	FILE *f = fopen(filename.c_str(), "rb");
	if (!f) {
	    errh->error("%s: %s", filename.c_str(), strerror(errno));
	    return -1;
	}


	Efont::Type1Reader *reader;
	int c = getc(f);
	ungetc(c, f);
	if (c == 128)
	    reader = new Efont::Type1PFBReader(f);
	else
	    reader = new Efont::Type1PFAReader(f);
	Efont::Type1Font *font = new Efont::Type1Font(*reader);
	delete reader;

	if (!font->ok()) {
	    errh->error("%s: no glyphs in dotless-J font", filename.c_str());
	    delete font;
	    return -1;
	}


	Vector<PermString> glyph_names;
	font->glyph_names(glyph_names);
	Vector<PermString>::iterator g = std::find(glyph_names.begin(), glyph_names.end(), "uni0237");
	if (g == glyph_names.end()) {
	    errh->error("%s: dotless-J font has no %<uni0237%> glyph", filename.c_str());
	    delete font;
	    return -1;
	}
	dj_glyph = g - glyph_names.begin();


	if (install_metrics) {
	    Metrics dj_metrics(font, 256);
	    dj_metrics.encode('j', U_DOTLESSJ, dj_glyph);
	    ::dotlessj_file_name = filename;
	    output_metrics(dj_metrics, font->font_name(), -1, _finfo, String(), String(), dj_name, dotlessj_dvips_include, errh);
	} else if (verbose)
	    errh->message("using %<%s%> for dotless-J font metrics", dj_name.c_str());


	return metrics.add_mapped_font(font, dj_name);

    } else
	return -1;
}
