mapTri(Dt_t * map, tri * tp)
{
    for (; tp; tp = tp->nxttri) {
	tp->v.i = vMap(map, tp->v.i);
	tp->v.j = vMap(map, tp->v.j);
    }
}
