startOp ( diOp Op )
{
	if ( Op == diAnd || Op == diOr )
		incIndent();

	o << "(";

	switch (Op)
	{
	case diErrorOp:
	default:
		fpp_unreachable();

	case diNot:
		o << "not";
		break;
	case diAnd:
		o << "and";
		break;
	case diOr:
		o << "or";
		break;
	case diExists:
		o << "some";
		break;
	case diForall:
		o << "all";
		break;
	case diGE:
		o << "atleast";
		break;
	case diLE:
		o << "atmost";
		break;
	}

	contOp(Op);
}
