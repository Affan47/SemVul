getLaTeXMarkup(docstring const & macro, docstring const & author,
			 docstring const & chgTime,
			 OutputParams const & runparams)
{
	if (macro.empty())
		return docstring();

	static docstring warned_author = docstring();
	docstring uncodable_author = warned_author;
	odocstringstream ods;

	ods << macro;


	docstring author_latexed;
	for (size_t n = 0; n < author.size(); ++n) {
		try {
			author_latexed += runparams.encoding->latexChar(author[n]);
		} catch (EncodingException & ) {
			if (runparams.dryrun) {
				ods << "<" << _("LyX Warning: ")
				    << _("uncodable character") << " '";
				ods.put(author[n]);
				ods << "'>";
			} else {
				LYXERR0("Omitting uncodable character '"
					<< docstring(1, author[n])
					<< "' in change author name!");
				uncodable_author = author;
			}
		}
	}
	ods << author_latexed << "}{" << chgTime << "}{";


	if (uncodable_author != warned_author) {
		frontend::Alert::warning(_("Uncodable character in author name"),
				support::bformat(_("The author name '%1$s',\n"
				  "used for change tracking, contains glyphs that cannot be\n"
				  "represented in the current encoding. The respective glyphs\n"
				  "will be omitted in the exported LaTeX file.\n\n"
				  "Choose an appropriate document encoding (such as utf8)\n"
				  "or change the spelling of the author name."), uncodable_author));
		warned_author = uncodable_author;
	}

	return ods.str();
}
}
