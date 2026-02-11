update(Dict_t * Q, Agnode_t * dest, Agnode_t * src, double len)
{
    double newlen = getdist(src) + len;
    double oldlen = getdist(dest);

    if (oldlen == 0) {
	setdist(dest, newlen);
	if (doPath) setprev(dest, src);
	dtinsert(Q, dest);
    } else if (newlen < oldlen) {
	dtdelete(Q, dest);
	setdist(dest, newlen);
	if (doPath) setprev(dest, src);
	dtinsert(Q, dest);
    }
}
