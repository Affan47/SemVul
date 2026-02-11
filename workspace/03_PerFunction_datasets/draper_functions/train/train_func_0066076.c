variable_set(variable_t *v, const char *value) {
	switch (v->type) {
		case VAR_INT:
		case VAR_MAP:
		{
			char *p;
			int tmp;

			if (!value || !(*value))
				return -2;

			tmp = strtol(value, &p, 0);

			if (*p != '\0')
				return -2;

			if (v->map) {
				int i;

				for (i = 0; v->map[i].label; i++) {
					if ((tmp & v->map[i].value) && (tmp & v->map[i].conflicts))
						return -2;
				}
			}

			*(int*)(v->ptr) = tmp;

			break;
		}

		case VAR_BOOL:
		{
			int tmp;

			if (!value)
				return -2;

			if ((tmp = on_off(value)) == -1)
				return -2;

			*(int*)(v->ptr) = tmp;

			break;
		}
		case VAR_THEME:
		case VAR_FILE:
		case VAR_DIR:
		case VAR_STR:
		{
			char **tmp = (char**)(v->ptr);

			xfree(*tmp);
			*tmp = xstrdup(value);


			break;
		}


		default:
			return -1;
	}


	if (v->notify)
		(v->notify)(v->name);

	query_emit_id(NULL, VARIABLE_CHANGED, &(v->name));
	return 0;
}
