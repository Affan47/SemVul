infoize(odocstream & os) const
{
	os << "xymatrix ";
	if (equal_spacing_) {
		switch (spacing_code_) {
		case '0':
		case 'R':
		case 'C':
			os << '!' << spacing_code_ << ' ';
		}
	} else {
		switch (spacing_code_) {
		case 'R':
		case 'C':
		case 'M':
		case 'W':
		case 'H':
		case 'L':
			os << spacing_code_ << ' '
			   << from_ascii(spacing_.asLatexString()) << ' ';
			break;
		default:
			if (!spacing_.empty())
				os << from_ascii(spacing_.asLatexString()) << ' ';
		}
	}
	InsetMathGrid::infoize(os);
}
