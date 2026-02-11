htmlize(HtmlStream & os) const
{
	switch (kind_) {
	case ATOP:
		os << MTag("span", "class='frac'")
			 << MTag("span", "class='numer'") << cell(0) << ETag("span")
			 << MTag("span", "class='numer'") << cell(1) << ETag("span")
			 << ETag("span");
		break;


	case OVER:
	case FRAC:
	case DFRAC:
	case TFRAC:
	case CFRAC:
	case CFRACLEFT:
	case CFRACRIGHT:
		os << MTag("span", "class='frac'")
			 << MTag("span", "class='numer'") << cell(0) << ETag("span")
			 << MTag("span", "class='denom'") << cell(1) << ETag("span")
			 << ETag("span");
		break;

	case NICEFRAC:
		os << cell(0) << '/' << cell(1);
		break;

	case UNITFRAC:
		if (nargs() == 3)
			os << cell(2) << ' ';
		os << cell(0) << '/' << cell(1);
		break;

	case UNIT:


		if (nargs() == 2)
			os << cell(0)
			   << MTag("span")
			   << cell(1)
			   << ETag("span");
		else
			os << MTag("span")
			   << cell(0)
			   << ETag("span");
	}
}
