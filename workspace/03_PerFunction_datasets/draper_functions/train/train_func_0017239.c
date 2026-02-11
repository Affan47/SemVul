ChainAdjust (MesomerData &md0, MesomerData &md1, double ratio, map<Object*, MesomerData> &positions)
{
	MesomeryChain *chain = md0.chain, *parent;
	MesomerData md;
	double x = 0., y = 0.;
	ratio -= 1.;
	list<Mesomer*>::reverse_iterator m, mend;
	list<struct MC*>::iterator c, cend;
	while (chain) {
		for (m = chain->mesomers.rbegin (); m != mend; m++) {
			if (*m == md1.m)
				return;
			md = positions[*m];
			x = (md.x - md1.x) * ratio;
			y = (md.y - md1.y) * ratio;
			md.r.x0 += x;
			md.r.x1 += x;
			md.x += x;
			md.dx += x;
			md.r.y0 += y;
			md.r.y1 += y;
			md.y += y;
			md.dy += y;
			positions[md.m] = md;
		}
		parent = chain->prev;
		if (parent == NULL)
			return;
		cend = parent->children.end ();
		for (c = parent->children.begin (); c != cend; c++) {
			if (*c == chain)
				continue;
			ChainMove (*c, x, y, positions);
		}
		parent = chain;
	}
}
