IoSQLite3_setTimeoutSeconds(IoSQLite3 *self, IoObject *locals, IoMessage *m)
{


	IoNumber *num = IoMessage_locals_numberArgAt_(m, locals, 0);
	IOASSERT(IoNumber_asDouble(num) >= 0, "SQLite timeout must be a positive number");
	DATA(self)->timeoutSeconds = IoNumber_asDouble(num);
	return self;
}
