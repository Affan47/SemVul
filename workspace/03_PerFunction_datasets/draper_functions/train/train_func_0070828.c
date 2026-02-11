infoize2(odocstream & os) const
{
	if (limits_)
		os << from_ascii(limits_ == 1 ? ", Displayed limits" : ", Inlined limits");
}
