translate_set(void)
{
    _set *s, *first;
    _point *cur;
    _vector *u;

    u = POP(_vector);
    first = s = POP(_set);
    while (s != NULL) {
	get_mem(cur, _point);
	cur->x = s->p->x + u->x;
	cur->y = s->p->y + u->y;
	s->p = cur;
	s = s->next;
    }
    PSH(first);
}
