view_line_exposed(ht_view *v, int y, int x1, int x2)
{
	ht_group *g=v->group;
	while (g) {
		if (y >= g->size.y && y < g->size.y+g->size.h) {
			if (x1 < g->size.x) x1 = g->size.x;
			if (x2 > g->size.x + g->size.w) x2 = g->size.x+g->size.w;
			ht_view *n = g->first;
			while (n && n!=v) n=n->next;
			if (n) {
				n=n->next;
				if (n)
				while (n) {
					if (!(n->options & VO_TRANSPARENT_CHARS)) {
						if ((y>=n->size.y) && (y<n->size.y+n->size.h)) {
							if (n->size.x<=x1) {
								if (n->size.x+n->size.w>=x2) {
									return 0;
								} else if (n->size.x+n->size.w>x1) {
									x1=n->size.x+n->size.w;
								}
							} else if (n->size.x<=x2) {
								if (n->size.x+n->size.w<x2) {
									if (!view_line_exposed(n, y, x1, n->size.x)) return 0;
									x1=n->size.x+n->size.w;
								} else {
									x2=n->size.x;
								}
							}
						}
					}
					n=n->next;
				}
			}
		} else break;
		v=g;
		g=g->group;
	}
	return 1;
}
