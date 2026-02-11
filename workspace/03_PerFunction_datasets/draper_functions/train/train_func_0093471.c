write(WriteStream & os) const
{
	MathEnsurer ensurer(os);
	os << "\\sqrt{" << cell(0) << '}';
}
