prepend(const rpt_expr::pointer &ep)
{
    trace(("rpt_expr::prepend(this = %08lX, ep = %08lX)\n{\n", (long)this,
        (long)ep.get()));
    if (nchild >= nchild_max)
    {
	size_t new_nchild_max = nchild_max * 2 + 4;
	rpt_expr::pointer *new_child = new rpt_expr::pointer [new_nchild_max];
	for (size_t j = 0; j < nchild; ++j)
	    new_child[j + 1] = child[j];
	delete [] child;
        child = new_child;
        nchild_max = new_nchild_max;
    }
    else
    {
	for (size_t j = nchild; j > 0; --j)
	    child[j] = child[j - 1];
    }
    nchild++;
    child[0] = ep;


    if (ep->pos)
    {
        if (!pos)
            pos = ep->pos;
        else
            pos = rpt_position::join(pos, ep->pos);
        assert(pos);
    }
    trace(("}\n"));
}
