IoSyslog_mask(IoSyslog *self, IoObject *locals, IoMessage *m)
{


	if (IoMessage_argCount(m) >= 1)
	{
		if (!DATA(self)->syslog_opened)
		{
			IoState_error_(IOSTATE, m, "Log must be opened before setting the logging mask");
			return IONIL(self);
		}

		DATA(self)->mask = IOREF(IoMessage_locals_listArgAt_(m, locals, 0));

		{
			List *list = IoList_rawList(DATA(self)->mask);

			LIST_FOREACH(list, i, v,
				DATA(self)->syslog_mask |= (int)CNUMBER(v);
			);

			setlogmask(DATA(self)->syslog_mask);
		}
	}

	return DATA(self)->mask;
}
