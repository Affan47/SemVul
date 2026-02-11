maple(MapleStream & os) const
{
	os << "diff(";
	for (idx_type idx = 0; idx < nargs(); ++idx) {
		if (idx != 0)
			os << ',';
		os << cell(idx);
	}
	os << ')';
}
