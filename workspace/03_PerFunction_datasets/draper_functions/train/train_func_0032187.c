find_TAGS(struct view *view, struct view *tags)
{
	const char *currpath = (tags ? tags : view)->text->path;
	char *path = allocate(strlen(currpath) + 8);
	char *slash;

	strcpy(path, currpath);
	if (tags) {
		view_close(tags);
		slash = strrchr(path, '/');
		if (slash)
			*slash = '\0';
	}
	for (; (slash = strrchr(path, '/')); *slash = '\0') {
		strcpy(slash+1, "TAGS");
		if (!access(path, R_OK)) {
			tags = view_open(path);
			if (tags && !(tags->text->flags & TEXT_CREATED)) {
				RELEASE(path);
				return tags;
			}
			view_close(tags);
		}
	}
	RELEASE(path);
	return NULL;
}
