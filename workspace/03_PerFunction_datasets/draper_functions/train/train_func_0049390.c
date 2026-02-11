eval_ytest (double y, GretlOp op, double test)
{
    int ret = 0;

    switch (op) {
    case OP_EQ:
	ret = (y == test);
	break;
    case OP_GT:
	ret = (y > test);
	break;
    case OP_LT:
	ret = (y < test);
	break;
    case OP_NEQ:
	ret = (y != test);
	break;
    case OP_GTE:
	ret = (y >= test);
	break;
    case OP_LTE:
	ret = (y <= test);
	break;
    default:
	break;
    }

    return ret;
}
