insertCompletion(Cursor & cur, docstring const & s,
					bool finished)
{
	if (displayMode() != DISPLAY_UNFOLDED)
		return InsetMathNest::insertCompletion(cur, s, finished);

	if (!completionSupported(cur))
		return false;


	docstring newName = name() + s;
	asArray(newName, cell(0));
	cur.bv().cursor().pos() = name().size();
	cur.screenUpdateFlags(Update::SinglePar);


	if (finished) {
		cur.bv().cursor().pop();
		++cur.bv().cursor().pos();
		cur.screenUpdateFlags(Update::SinglePar);
	}

	return true;
}
