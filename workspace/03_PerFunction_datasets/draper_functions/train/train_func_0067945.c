handleNest(MathAtom const & a, int c)
{

	MathAtom t = a;
	asArray(cap::grabAndEraseSelection(*this), t.nucleus()->cell(c));
	insert(t);
	posBackward();
	pushBackward(*nextInset());
}
