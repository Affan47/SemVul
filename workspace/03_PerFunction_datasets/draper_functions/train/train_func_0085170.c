getVectorAsStringLine(const core::vector2df& v, core::stringc& s) const
{
	s = core::stringc(v.X);
	s += " ";
	s += core::stringc(-v.Y);
	s += "\n";
}
