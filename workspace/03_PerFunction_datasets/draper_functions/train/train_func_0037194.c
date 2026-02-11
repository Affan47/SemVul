ct_visual_string(const Char *s)
{
	static Char *buff = NULL;
	static size_t buffsize = 0;
	void *p;
	Char *dst;
	ssize_t used = 0;

	if (!s)
		return NULL;
	if (!buff) {
	    buffsize = CT_BUFSIZ;
	    buff = el_malloc(buffsize * sizeof(*buff));
	}
	dst = buff;
	while (*s) {
		used = ct_visual_char(dst, buffsize - (dst - buff), *s);
		if (used == -1) {
			used = dst - buff;
			buffsize += CT_BUFSIZ;
			p = el_realloc(buff, buffsize * sizeof(*buff));
			if (p == NULL)
				goto out;
			buff = p;
			dst = buff + used;

		}
		else
		    ++s;
		dst += used;
	}
	if (dst >= (buff + buffsize)) {
		buffsize += 1;
		p = el_realloc(buff, buffsize * sizeof(*buff));
		if (p == NULL)
			goto out;
		buff = p;
		dst = buff + buffsize - 1;
	}
	*dst = 0;
	return buff;
out:
	el_free(buff);
	buffsize = 0;
	return NULL;
}
