get_aino (Unit *unit, a_inode *base, const TCHAR *rel, int *err)
{
	TCHAR *tmp;
	TCHAR *p;
	a_inode *curr;
	int i;

	aino_test (base);

	*err = 0;
	TRACE((_T("get_path(%s,%s)\n"), base->aname, rel));


	for (i = 0; rel[i] && rel[i] != '/' && rel[i] != ':'; i++)
		;
	if (':' == rel[i])
		rel += i+1;

	tmp = my_strdup (rel);
	p = tmp;
	curr = base;

	while (*p) {

		if (*p == '/') {
			if (curr->parent != 0)
				curr = curr->parent;
			p++;
		} else {
			a_inode *next;

			TCHAR *component_end;
			component_end = _tcschr (p, '/');
			if (component_end != 0)
				*component_end = '\0';
			next = lookup_child_aino (unit, curr, p, err);
			if (next == 0) {

				if (*err != ERROR_OBJECT_NOT_AROUND || component_end != 0)
					curr = 0;

				break;
			}
			curr = next;
			if (component_end)
				p = component_end+1;
			else
				break;

		}
	}
	xfree (tmp);
	return curr;
}
