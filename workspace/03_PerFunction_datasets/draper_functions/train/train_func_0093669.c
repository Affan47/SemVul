IoList_each(IoList *self, IoObject *locals, IoMessage *m)
{
	IoState *state = IOSTATE;
	IoObject *result = IONIL(self);
	IoMessage *doMessage = IoMessage_rawArgAt_(m, 0);
	List *list = DATA(self);

	IoState_pushRetainPool(state);

	LIST_SAFEFOREACH(list, i, v,
		IoState_clearTopPool(state);
		result = IoMessage_locals_performOn_(doMessage, locals, (IoObject *)v);
		if (IoState_handleStatus(IOSTATE)) goto done;
	);

done:
	IoState_popRetainPoolExceptFor_(state, result);
	return result;
}
