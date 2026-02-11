node_set_type(node N, int Tp, int side)
{
    if (N == 0)
	bad_error("null node to node_get_type");
    if (side == LEFT)
	return N->LT;
    else if (side == RIGHT)
	return N->RT=Tp;
    bad_error("bad side given in node_get_type");
    return 0;
}
