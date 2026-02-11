drawSelection(PainterInfo & pi, int x, int y) const
{

	if (cells_.size() > 0)
		InsetMathNest::drawSelection(pi, x, y);
}
