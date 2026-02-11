x_cutval(edge_t * f)
{
    node_t *v;
    edge_t *e;
    int i, sum, dir;


    if (ND_par(agtail(f)) == f) {
	v = agtail(f);
	dir = 1;
    } else {
	v = aghead(f);
	dir = -1;
    }

    sum = 0;
    for (i = 0; (e = ND_out(v).list[i]); i++)
	sum += x_val(e, v, dir);
    for (i = 0; (e = ND_in(v).list[i]); i++)
	sum += x_val(e, v, dir);
    ED_cutvalue(f) = sum;
}
