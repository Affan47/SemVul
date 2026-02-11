IoList_foreach(IoList *self, IoObject *locals, IoMessage *m)
{


	IoState *state = IOSTATE;
	IoObject *result = IONIL(self);
	IoSymbol *slotName = NULL;
	IoSymbol *valueName;
	IoMessage *doMessage;
	List *list = DATA(self);

	if (IoMessage_argCount(m) == 1)
	{
		return IoList_each(self, locals, m);
	}

	IoMessage_foreachArgs(m, self, &slotName, &valueName, &doMessage);

	IoState_pushRetainPool(state);

	if (slotName)
	{
		LIST_SAFEFOREACH(list, i, value,
			IoState_clearTopPool(state);
			IoObject_setSlot_to_(locals, slotName, IONUMBER(i));
			IoObject_setSlot_to_(locals, valueName, (IoObject *)value);
			result = IoMessage_locals_performOn_(doMessage, locals, locals);
			if (IoState_handleStatus(IOSTATE)) goto done;
		);
	}
	else
	{
		LIST_SAFEFOREACH(list, i, value,
			IoState_clearTopPool(state);
			IoObject_setSlot_to_(locals, valueName, (IoObject *)value);
			result = IoMessage_locals_performOn_(doMessage, locals, locals);
			if (IoState_handleStatus(IOSTATE)) goto done;
		);
	}

done:
		IoState_popRetainPoolExceptFor_(state, result);
	return result;
}
