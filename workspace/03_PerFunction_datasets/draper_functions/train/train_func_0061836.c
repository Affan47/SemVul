Path_Print(const struct Path *path)
{
	const struct PathElement *p;

	TAILQ_FOREACH(p, path, link)
		printf("%s ", p->dir->name);
}
