tm_work_object_find(TMWorkObject *work_object, const char *file_name
  , gboolean name_only)
{
	if ((NULL != work_object) && (work_object->type > 0) &&
		  (work_object->type < s_work_object_subclasses->len) &&
		  (s_work_object_subclasses->pdata[work_object->type] != NULL))
	{
		TMFindFunc find_func =
		  ((TMWorkObjectClass *)s_work_object_subclasses->pdata[work_object->type])->find_func;
		if (NULL == find_func)
		{
			if (name_only)
			{
				const char *short_name = strrchr(file_name, '/');
				if (short_name)
					++ short_name;
				else
					short_name = file_name;
				if (0 == strcmp(work_object->short_name, short_name))
					return work_object;
				else
					return NULL;
			}
			else
			{
				char *path = tm_get_real_path(file_name);
				int cmp = strcmp(work_object->file_name, file_name);
				g_free(path);
				if (0 == cmp)
					return work_object;
				else
					return NULL;
			}
		}
		else
			return find_func(work_object, file_name, name_only);
	}
	return NULL;
}
