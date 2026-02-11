vrml_node_point(GVJ_t *job, node_t *n, pointf p)
{
    pointf rv;


    if (job->rotation) {
	rv.x = ( (p.y - job->pad.y) - ND_coord(n).y + ND_lw(n)     ) * Scale + NODE_PAD;
	rv.y = (-(p.x - job->pad.x) + ND_coord(n).x + ND_ht(n) / 2.) * Scale + NODE_PAD;
    } else {
	rv.x = ( (p.x - job->pad.x) - ND_coord(n).x + ND_lw(n)     ) * Scale + NODE_PAD;
	rv.y = (-(p.y - job->pad.y) + ND_coord(n).y + ND_ht(n) / 2.) * Scale + NODE_PAD;
    }
    return rv;
}
