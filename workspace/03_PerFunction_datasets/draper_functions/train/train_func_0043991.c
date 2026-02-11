addcmd(int f, char *s)
{
	struct cmd *h;

	h = mymalloc(sizeof(struct cmd));
	if( tail) {
		tail->next = h;
		h->next = 0;
		h->prev = tail;
		tail = h;
	} else {
		tail = h;
		h->next = h->prev = 0;
	}
	h->field = f;
	h->text = my_strdup( s);
	current = 0;
}
