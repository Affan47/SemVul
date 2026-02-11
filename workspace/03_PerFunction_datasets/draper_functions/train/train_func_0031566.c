tm_work_object_update(TMWorkObject *work_object, gboolean force
  , gboolean recurse, gboolean update_parent)
{
	if ((NULL != work_object) && (work_object->type > 0) &&
		  (work_object->type < s_work_object_subclasses->len) &&
		  (s_work_object_subclasses->pdata[work_object->type] != NULL))
	{
		TMUpdateFunc update_func =
		  ((TMWorkObjectClass *)s_work_object_subclasses->pdata[work_object->type])->update_func;
		if (NULL != update_func)
			return update_func(work_object, force, recurse, update_parent);
	}
	return FALSE;
}
