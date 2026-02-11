infoize(odocstream & os) const
{
	switch (kind_) {
	case AMS_BOLD:
		os << "Boldsymbol ";
		break;
	case BM_BOLD:
		os << "Boldsymbol (bm)";
		break;
	case BM_HEAVY:
		os << "Heavysymbol (bm)";
		break;
	}
}
