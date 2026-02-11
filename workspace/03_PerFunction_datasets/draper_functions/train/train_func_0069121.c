iks_find_with_attrib (iks *x, const char *tagname, const char *attrname, const char *value)
{
	iks *y;

	if (NULL == x) return NULL;

	if (tagname) {
		for (y = IKS_TAG_CHILDREN (x); y; y = y->next) {
			if (IKS_TAG == y->type
				&& strcmp (IKS_TAG_NAME (y), tagname) == 0
				&& iks_strcmp (iks_find_attrib (y, attrname), value) == 0) {
					return y;
			}
		}
	} else {
		for (y = IKS_TAG_CHILDREN (x); y; y = y->next) {
			if (IKS_TAG == y->type
				&& iks_strcmp (iks_find_attrib (y, attrname), value) == 0) {
					return y;
			}
		}
	}
	return NULL;
}
