write(WriteStream & os) const
{
	MathEnsurer ensurer(os);
	os << "\\begin{" << name_ << '}';
	InsetMathGrid::write(os);
	os << "\\end{" << name_ << '}';
}
