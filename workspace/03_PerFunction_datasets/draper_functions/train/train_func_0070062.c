extractDets(MathData & ar)
{
	Buffer * buf = ar.buffer();

	for (MathData::iterator it = ar.begin(); it != ar.end(); ++it) {
		InsetMathDelim const * del = (*it)->asDelimInset();
		if (!del)
			continue;
		if (!del->isAbs())
			continue;
		*it = MathAtom(new InsetMathExFunc(buf, from_ascii("det"), del->cell(0)));
	}

}
