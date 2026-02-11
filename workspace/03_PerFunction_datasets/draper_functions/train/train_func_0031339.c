mono_mlist_prepend (MonoMList* list, MonoObject *data)
{
	MonoMList* res = mono_mlist_alloc (data);
	if (list)
		MONO_OBJECT_SETREF (res, next, list);
	return res;
}
