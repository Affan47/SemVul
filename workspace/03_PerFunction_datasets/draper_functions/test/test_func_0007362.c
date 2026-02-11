write(WriteStream & os) const
{
	MathEnsurer ensurer(os);

	if (os.fragile())
		os << "\\protect";
	os << "\\begin{" << name_ << '}';

	char const v = verticalAlignment();
	if (v == 't' || v == 'b')
		os << '[' << v << ']';
	os << '{' << horizontalAlignments() << "}\n";

	InsetMathGrid::write(os);

	if (os.fragile())
		os << "\\protect";
	os << "\\end{" << name_ << '}';


}
