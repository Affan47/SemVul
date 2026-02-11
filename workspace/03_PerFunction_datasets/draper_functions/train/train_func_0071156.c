seaudit_sort_create_from_sort(const seaudit_sort_t * sort)
{
	seaudit_sort_t *s;
	if (sort == NULL) {
		errno = EINVAL;
		return NULL;
	}
	if ((s = calloc(1, sizeof(*s))) == NULL) {
		return NULL;
	}
	s->name = sort->name;
	s->comp = sort->comp;
	s->support = sort->support;
	s->direction = sort->direction;
	return s;
}
