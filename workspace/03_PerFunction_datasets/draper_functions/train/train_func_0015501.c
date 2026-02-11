IoSeq_foreach(IoSeq *self, IoObject *locals, IoMessage *m)
{


	IoObject *result = IONIL(self);
	IoMessage *doMessage;

	IoSymbol *indexSlotName;
	IoSymbol *characterSlotName;

	size_t i;

	if (IoMessage_argCount(m) == 1)
	{
		return IoSeq_each(self, locals, m);
	}

	IoMessage_foreachArgs(m, self, &indexSlotName, &characterSlotName, &doMessage);

	IoState_pushRetainPool(IOSTATE);

	for (i = 0; i < UArray_size(DATA(self)); i ++)
	{
		IoState_clearTopPool(IOSTATE);

		if (indexSlotName)
		{
			IoObject_setSlot_to_(locals, indexSlotName, IONUMBER(i));
		}

		if(UArray_isFloatType(DATA(self)))
		{
			IoObject_setSlot_to_(locals, characterSlotName, IONUMBER(UArray_doubleAt_(DATA(self), i)));
		}
		else
		{
			IoObject_setSlot_to_(locals, characterSlotName, IONUMBER(UArray_longAt_(DATA(self), i)));
		}
		result = IoMessage_locals_performOn_(doMessage, locals, locals);

		if (IoState_handleStatus(IOSTATE))
		{
			goto done;
		}
	}
done:
		IoState_popRetainPoolExceptFor_(IOSTATE, result);
	return result;
}
