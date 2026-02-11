bch_keybuf_check_overlapping(struct keybuf *buf, struct bkey *start,
				  struct bkey *end)
{
	bool ret = false;
	struct keybuf_key *p, *w, s;
	s.key = *start;

	if (bkey_cmp(end, &buf->start) <= 0 ||
	    bkey_cmp(start, &buf->end) >= 0)
		return false;

	spin_lock(&buf->lock);
	w = RB_GREATER(&buf->keys, s, node, keybuf_nonoverlapping_cmp);

	while (w && bkey_cmp(&START_KEY(&w->key), end) < 0) {
		p = w;
		w = RB_NEXT(w, node);

		if (p->private)
			ret = true;
		else
			__bch_keybuf_del(buf, p);
	}

	spin_unlock(&buf->lock);
	return ret;
}
