ClearDirectives(int rehash)

{
	struct Directive *tmp;
	int ii;

	for (tmp = directives; tmp->name; ++tmp)
	{
		if (rehash &&
		        ((tmp->flag == D_NORUNTIME) || (tmp->flag == D_REQUIRED)))
			continue;

		for (ii = 0; ii < PARAM_MAX; ii++)
		{
			if (!tmp->param[ii].type)
				break;

			switch (tmp->param[ii].type)
			{
			case PARAM_STRING:
				{
					MyFree(*(char **) tmp->param[ii].ptr);
					*(char **) tmp->param[ii].ptr = NULL;
					break;
				}

			case PARAM_TIME:
				{
					*(long **) tmp->param[ii].ptr = NULL;
					break;
				}

			case PARAM_INT:
			case PARAM_SET:
			case PARAM_PORT:
				{
					*(int *) tmp->param[ii].ptr = 0;
					break;
				}

			default:
				break;
			}
		}
	}
}
