get_link_kind(const char *id)
{
	void *dlh;
	char buf[256];
	struct link_util *l;

	for (l = linkutil_list; l; l = l->next)
		if (strcmp(l->id, id) == 0)
			return l;

	snprintf(buf, sizeof(buf), LIBDIR "/ip/link_%s.so", id);
	dlh = dlopen(buf, RTLD_LAZY);
	if (dlh == NULL) {

		dlh = BODY;
		if (dlh == NULL) {
			dlh = BODY = dlopen(NULL, RTLD_LAZY);
			if (dlh == NULL)
				return NULL;
		}
	}

	snprintf(buf, sizeof(buf), "%s_link_util", id);
	l = dlsym(dlh, buf);
	if (l == NULL)
		return NULL;

	l->next = linkutil_list;
	linkutil_list = l;
	return l;
}
