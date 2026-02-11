mx_free()
{
	struct column *tmp, *c = first;
	while (c) {
		tmp = c;
		SWITCH(c);
		xfree(tmp->caption);
		xfree(tmp);
	}
	first = last = NULL;
}
