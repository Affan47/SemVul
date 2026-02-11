setcorner1(PROCESS *p, int i, int j, int k)
{

    CORNER *c = (CORNER *) mycalloc(1, sizeof(CORNER));
    int index = HASH(i, j, k);
    CORNERLIST *l = p->corners[index];
    c->i = i; c->x = p->start.x+((double)i-.5)*p->size;
    c->j = j; c->y = p->start.y+((double)j-.5)*p->size;
    c->k = k; c->z = p->start.z+((double)k-.5)*p->size;
    for (; l != NULL; l = l->next)
	if (l->i == i && l->j == j && l->k == k) {
	    c->value = l->value;
	    return c;
	    }
    l = (CORNERLIST *) mycalloc(1, sizeof(CORNERLIST));
    l->i = i; l->j = j; l->k = k;
    l->value = c->value = function(c->x, c->y, c->z);
    l->next = p->corners[index];
    p->corners[index] = l;
    return c;
}
