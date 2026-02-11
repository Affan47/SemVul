hcb_insert(struct worker *wrk, struct hcb_root *root, struct objhead *oh, int has_lock)
{
	volatile uintptr_t *p;
	uintptr_t pp;
	struct hcb_y *y, *y2;
	struct objhead *oh2;
	unsigned s, s2;

	p = &root->origo;
	pp = *p;
	if (pp == 0) {
		if (!has_lock)
			return (NULL);
		*p = hcb_r_node(oh);
		return (oh);
	}

	while(hcb_is_y(pp)) {
		y = hcb_l_y(pp);
		CHECK_OBJ_NOTNULL(y, HCB_Y_MAGIC);
		assert(y->ptr < DIGEST_LEN);
		s = (oh->digest[y->ptr] & y->bitmask) != 0;
		assert(s < 2);
		p = &y->leaf[s];
		pp = *p;
	}

	if (pp == 0) {

		assert(!has_lock);
		return (NULL);
	}

	assert(hcb_is_node(pp));


	oh2 = hcb_l_node(pp);
	CHECK_OBJ_NOTNULL(oh2, OBJHEAD_MAGIC);
	if (!memcmp(oh2->digest, oh->digest, DIGEST_LEN))
		return (oh2);

	if (!has_lock)
		return (NULL);


	CAST_OBJ_NOTNULL(y2, wrk->nhashpriv, HCB_Y_MAGIC);
	wrk->nhashpriv = NULL;
	(void)hcb_crit_bit(oh, oh2, y2);
	s2 = (oh->digest[y2->ptr] & y2->bitmask) != 0;
	assert(s2 < 2);
	y2->leaf[s2] = hcb_r_node(oh);
	s2 = 1-s2;

	p = &root->origo;
	assert(*p != 0);

	while(hcb_is_y(*p)) {
		y = hcb_l_y(*p);
		CHECK_OBJ_NOTNULL(y, HCB_Y_MAGIC);
		assert(y->critbit != y2->critbit);
		if (y->critbit > y2->critbit)
			break;
		assert(y->ptr < DIGEST_LEN);
		s = (oh->digest[y->ptr] & y->bitmask) != 0;
		assert(s < 2);
		p = &y->leaf[s];
	}
	y2->leaf[s2] = *p;
	VWMB();
	*p = hcb_r_y(y2);
	return(oh);
}
