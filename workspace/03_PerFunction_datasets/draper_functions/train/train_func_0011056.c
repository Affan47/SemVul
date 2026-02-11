raise_event(OBJECT *observer, void *object, int func_id, int nparam)
{
	bool stop_event;
	CLASS *class;
	CLASS_DESC_METHOD *desc;
	void *old_last;
	bool result;

	func_id--;

	if (OBJECT_is_class(observer))
		class = (CLASS *)observer;
	else
		class = OBJECT_class(observer);

	desc = &class->table[func_id].desc->method;

	old_last = EVENT_Last;
	EVENT_Last = object;


	stop_event = GAMBAS_StopEvent;
	GAMBAS_StopEvent = FALSE;

	EXEC_public_desc(class, observer, desc, nparam);

	if (RP->type == T_VOID)
		result = FALSE;
	else
		result = RP->_boolean.value != 0;

	if (GAMBAS_StopEvent)
		result = TRUE;

	GAMBAS_StopEvent = stop_event;


	EVENT_Last = old_last;

	EXEC_release_return_value();

	return result;
}
