menu_free(struct widget *m)
{
	struct widget *w, *w2;

	if (m == NULL)
		return m;

	for (w = m->kids; w;) {
		w2 = w->next;
		line_free(w);
		w = w2;
	}

	xfree(m->data);
	return xfree(m);
}
