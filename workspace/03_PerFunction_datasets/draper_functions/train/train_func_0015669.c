OBJECT_create(CLASS *class, const char *name, void *parent, int nparam)
{
	void *ob;
	void *save;
	char *save_name;


	save = _object;
	save_name = _object_name;

	ON_ERROR(error_OBJECT_create)
	{
		_object_name = EVENT_enter_name(name);
		_object = ob = OBJECT_new(class, name, parent);
		if (OBJECT_set_pointer)
		{
			*OBJECT_set_pointer = ob;
			OBJECT_ref(ob);
			OBJECT_set_pointer = NULL;
		}

		OBJECT_lock(ob, TRUE);
		EXEC_special_inheritance(SPEC_NEW, class, ob, nparam, TRUE);
		OBJECT_lock(ob, FALSE);

		error_OBJECT_create();
	}
	END_ERROR

	_object = save;
	_object_name = save_name;

	return ob;
}
