maxima(MaximaStream & os) const
{
	if (symbol_ == "int")
		os << "integrate(";
	else
		os << symbol_ << '(';

	if (cell(0).size())
		os << cell(0) << ',';
	else
		os << '1' << ',';
	if (hasScripts())
		os << cell(1) << ',' << cell(2) << ',' << cell(3) << ')';
	else
		os << cell(1) << ')';
}
