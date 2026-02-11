interpret_branch_name(const char *name, struct strbuf *buf)
{
	char *cp;
	struct branch *upstream;
	int namelen = strlen(name);
	int len = interpret_nth_prior_checkout(name, buf);
	int tmp_len;

	if (!len)
		return len;
	if (0 < len && len == namelen)
		return len;
	else if (0 < len) {

		struct strbuf tmp = STRBUF_INIT;
		int used = buf->len;
		int ret;

		strbuf_add(buf, name + len, namelen - len);
		ret = interpret_branch_name(buf->buf, &tmp);

		if (ret < 0) {
			strbuf_setlen(buf, used);
			return len;
		}
		strbuf_reset(buf);
		strbuf_addbuf(buf, &tmp);
		strbuf_release(&tmp);

		return ret - used + len;
	}

	cp = strchr(name, '@');
	if (!cp)
		return -1;
	tmp_len = upstream_mark(cp, namelen - (cp - name));
	if (!tmp_len)
		return -1;
	len = cp + tmp_len - name;
	cp = xstrndup(name, cp - name);
	upstream = branch_get(*cp ? cp : NULL);
	if (!upstream
	    || !upstream->merge
	    || !upstream->merge[0]->dst)
		return error("No upstream branch found for '%s'", cp);
	free(cp);
	cp = shorten_unambiguous_ref(upstream->merge[0]->dst, 0);
	strbuf_reset(buf);
	strbuf_addstr(buf, cp);
	free(cp);
	return len;
}
