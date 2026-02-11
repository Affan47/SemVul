digest_start_copy(c, r)
     Character *c;
     Character *r;
{
    for(;;) {
	r->type = c->type;
	r->c1 = c->c1;
	r->c2 = c->c2;
	if ((r->type == OTHER) && (r->c1 == 0)) return;
	++r, ++c;
    }
}
