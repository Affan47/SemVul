completionSupported(Cursor const & cur) const
{
	if (displayMode() != DISPLAY_UNFOLDED)
		return InsetMathNest::completionSupported(cur);

	return lyxrc.completion_popup_math
		&& displayMode() == DISPLAY_UNFOLDED
		&& cur.bv().cursor().pos() == int(name().size());
}
