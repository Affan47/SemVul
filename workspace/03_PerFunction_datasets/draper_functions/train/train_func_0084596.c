write(WriteStream & os) const
{
	ModeSpecifier specifier(os, TEXT_MODE);
	os << '\\' << name_ << '{' << cell(0) << '}';
}
