flushlines()
{
	std::string prefix;

	textAttributes attr;

	if (currentQuoteLevel)
	{
		for (size_t i=0; i<currentQuoteLevel; ++i)
		{
			attr.fgcolor=
				quote_colors[ (i % (sizeof(quote_colors)/
						    sizeof(quote_colors[0])))]
				->fcolor;


			prefix += (std::string)attr;

			prefix += ">";
		}

		prefix += " ";
	}

	if (messagePtr)
	{
		messagePtr->reformatFindUrls(wrapped_lines, attr);

		for (std::vector<std::string>::iterator b(wrapped_lines.begin()),
			     e(wrapped_lines.end()); b != e; ++b)
			messagePtr->reformatAddLine(prefix + *b,
						    CursesMessage::LineIndex::ATTRIBUTES);
	}

	wrapped_lines.clear();
}
