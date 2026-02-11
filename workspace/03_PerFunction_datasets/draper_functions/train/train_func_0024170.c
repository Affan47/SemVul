cycle_entries(struct palette *c, int direction)
{
    int i;
    int i1, i2, i3;
    rgb_t *co;
    if (direction > 0)
	direction %= c->size - 1;
    else
	direction = -((-direction) % (c->size - 1));
    if (!direction)
	return;
    co = (rgb_t *) malloc(c->end * sizeof(rgb_t));
    memcpy(co, c->rgb, sizeof(*co) * c->end);
    i3 = (c->size - 1 + direction) % (c->size - 1) + 1;
    for (i = 1; i < c->size; i++) {
	i1 = c->pixels[i];
	i2 = c->pixels[i3];
	c->rgb[i1][0] = co[i2][0];
	c->rgb[i1][1] = co[i2][1];
	c->rgb[i1][2] = co[i2][2];
	i3++;
	if (i3 >= c->size)
	    i3 = 1;
    }
    free(co);
}
