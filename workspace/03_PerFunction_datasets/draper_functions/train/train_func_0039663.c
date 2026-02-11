computeToCopy(const mail::mimestruct &section,
		const set<string> &whatNotToCopy)
{
	list<MIMEACTION>::iterator p;

	if (whatNotToCopy.count(section.mime_id) > 0)
	{
		parseTree.push_back(MIMEACTION(section, false, true));
		p=parseTree.end();
		return --p;
	}

	size_t n=section.getNumChildren();

	if (n == 0)
	{


		parseTree.push_back(MIMEACTION(section, true, false));
		p=parseTree.end();
		return --p;
	}

	vector< list<MIMEACTION>::iterator > subsections;

	size_t i;

	bool somethingCopied=false;
	bool somethingNotCopied=false;

	for (i=0; i<n; i++)
	{
		p=computeToCopy(*section.getChild(i), whatNotToCopy);

		if (p->somethingNotCopied)
			somethingNotCopied=true;

		if (!p->somethingCopied)
			continue;

		somethingCopied=true;
		subsections.push_back(p);
	}

	parseTree.push_back(MIMEACTION(section, somethingCopied,
				       somethingNotCopied));

	p=parseTree.end();
	--p;

	p->subsections=subsections;
	return p;
}
