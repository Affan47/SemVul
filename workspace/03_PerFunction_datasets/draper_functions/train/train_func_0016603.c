IoObject_defaultPrint(IoObject *self)
{
	if (ISSYMBOL(self))
	{
		IoSeq_rawPrint(self);
	}
	else if (ISNUMBER(self))
	{
		IoNumber_print(self);
	}
	else
	{
		IoState_print_(IOSTATE, "%s_%p", IoObject_name(self), self);

		if (ISMESSAGE(self))
		{
			IoState_print_(IOSTATE, " '%s'", CSTRING(IoMessage_name(self)));
		}
	}
}
