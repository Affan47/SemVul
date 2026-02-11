asLatexString() const
{
	ostringstream os;
	switch (unit_) {
	case PTW:
		os << val_ / 100.0 << "\\textwidth";
		break;
	case PCW:
		os << val_ / 100.0 << "\\columnwidth";
		break;
	case PPW:
		os << val_ / 100.0 << "\\paperwidth";
		break;
	case PLW:
		os << val_ / 100.0 << "\\linewidth";
		break;
	case PTH:
		os << val_ / 100.0 << "\\textheight";
		break;
	case PPH:
		os << val_ / 100.0 << "\\paperheight";
		break;
	default:
		os << val_ << unit_name[unit_];
	  break;
	}
	return os.str();
}
