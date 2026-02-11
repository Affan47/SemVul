write(WriteStream & os) const
{
	MathEnsurer ensurer(os);
	if (os.fragile())
		os << "\\protect";
	os << "\\begin{cases}\n";
	InsetMathGrid::write(os);
	if (os.fragile())
		os << "\\protect";
	os << "\\end{cases}";
}
