GB_Raise(void *object, int event_id, int nparam, ...)
{
	OBJECT *parent;
	int func_id;
	int result;
	va_list args;
	bool arg;
	COBSERVER *obs;
	void *save_GB_Raise_unref;
	char save_GB_Raise_nparam;

	if (GAMBAS_DoNotRaiseEvent)
		return FALSE;

	if (!OBJECT_is_valid(object) || !OBJECT_has_events(object))
		return FALSE;

	save_GB_Raise_unref = _GB_Raise_unref;
	save_GB_Raise_nparam = _GB_Raise_nparam;

	ON_ERROR(error_GB_Raise)
	{
		OBJECT_REF(object, "GB_Raise");
		_GB_Raise_unref = object;

		arg = nparam < 0;
		nparam = abs(nparam);

		if (!arg)
		{
			va_start(args, nparam);
			push(nparam, args);
			va_end(args);
		}

		_GB_Raise_nparam = nparam;

		result = FALSE;


		LIST_for_each(obs, OBJECT_event(object)->observer)
		{
			parent = OBJECT_active_parent(obs);
			if (!parent)
				continue;
			if (obs->after)
				continue;


			func_id = get_event_func_id(obs->event, event_id);
			if (!func_id)
				continue;

			if (!OBJECT_is_valid(parent))
			{
				OBJECT_detach(object);
				continue;
			}

			EXEC_dup(nparam);
			result = raise_event(parent, object, func_id, nparam);

			if (result)
				goto __RETURN;
		}


		parent = OBJECT_active_parent(object);
		if (parent)
		{
			func_id = get_event_func_id(OBJECT_event(object)->event, event_id);
			if (func_id)
			{
				#if DEBUG_EVENT
					CLASS *class = OBJECT_class(object);
					printf("GB_Raise(%p, %d, %s)\n", object, event_id, class->event[event_id].name);
					printf("func_id = %d  parent = (%s %p)\n", func_id, parent->class->name, parent);
					if (OBJECT_is_locked(parent))
						printf("parent is locked!\n");
					fflush(NULL);
				#endif

				if (!OBJECT_is_valid(parent))
					OBJECT_detach(object);
				else
				{
					EXEC_dup(nparam);
					result = raise_event(parent, object, func_id, nparam);
					if (result)
						goto __RETURN;
				}
			}
		}


		LIST_for_each(obs, OBJECT_event(object)->observer)
		{
			parent = OBJECT_active_parent(obs);
			if (!parent)
				continue;
			if (!obs->after)
				continue;


			func_id = get_event_func_id(obs->event, event_id);
			if (!func_id)
				continue;

			if (!OBJECT_is_valid(parent))
			{
				OBJECT_detach(object);
				continue;
			}

			EXEC_dup(nparam);
			result = raise_event(parent, object, func_id, nparam);
			if (result)
				goto __RETURN;
		}

__RETURN:

		RELEASE_MANY(SP, nparam);
		OBJECT_UNREF(object, "GB_Raise");
	}
	END_ERROR

	_GB_Raise_unref = save_GB_Raise_unref;
	_GB_Raise_nparam = save_GB_Raise_nparam;

	return result;
}
