ffe(node_t * u, elist uL, node_t * v, elist vL)
{
    int i;
    edge_t *e;

    if ((uL.size > 0) && (vL.size > 0)) {
	if (uL.size < vL.size) {
	    for (i = 0; (e = uL.list[i]); i++)
		if (aghead(e) == v)
		    break;
	} else {
	    for (i = 0; (e = vL.list[i]); i++)
		if (agtail(e) == u)
		    break;
	}
    } else
	e = 0;
    return e;
}
