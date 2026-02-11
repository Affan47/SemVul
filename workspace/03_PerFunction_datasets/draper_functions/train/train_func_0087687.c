replaceNested(
	MathData & ar,
	TestItemFunc testOpen,
	TestItemFunc testClose,
	ReplaceArgumentFunc replaceArg)
{
	Buffer * buf = ar.buffer();


	for (size_t i = 0; i < ar.size(); ++i) {

		if (!testOpen(ar[i]))
			continue;


		MathData::iterator it = ar.begin() + i;
		MathData::iterator jt = endNestSearch(it, ar.end(), testOpen, testClose);
		if (jt == ar.end())
			continue;


		ar[i] = replaceArg(MathData(buf, it + 1, jt));
		ar.erase(it + 1, jt + 1);
	}
}
