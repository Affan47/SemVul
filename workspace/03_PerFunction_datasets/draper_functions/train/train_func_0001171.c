next_Area(int parsed, list l, g_areas g, msg * m)
{
    if (parsed == NORMAL) {
	if (l->size == 0)
	    return 0;
	else {
	    msg tmp;

	    memcpy(&tmp, l->head->m, sizeof(msg));
	    *m = tmp;
	    removeNode(l);
	    return 1;
	}
    }
    else {
	return next(g, m);
    }
}
