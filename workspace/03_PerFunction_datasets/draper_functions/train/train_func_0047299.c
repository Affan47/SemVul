write(WriteStream & os) const
{
	MathEnsurer ensurer(os);
	os << '\\' << name_;
	if (cell(1).size())
		os << '[' << cell(1) << ']';
	os << '{' << cell(0) << '}';
}
