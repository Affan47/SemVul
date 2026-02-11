IoSystemCall_asyncRun(IoSystemCall *self, IoObject *locals, IoMessage *m)
{


	IoSymbol *command = IoMessage_locals_symbolArgAt_(m, locals, 0);
	List *args = IoList_rawList(IoMessage_locals_listArgAt_(m, locals, 1));
	IoMap *envMap = IoMessage_locals_mapArgAt_(m, locals, 2);
	List *envKeys = IoList_rawList(IoMap_rawKeys(envMap));
	int err;


	FILE *fchildin;
	FILE *fchildout;
	FILE *fchilderr;

	IoSystemCall_rawClose(self);


	callsystem_pipe(DATA(self)->stdin_child);
	callsystem_pipe(DATA(self)->stdout_child);
	callsystem_pipe(DATA(self)->stderr_child);


	fchildin  = callsystem_fdopen(DATA(self)->stdin_child,  CALLSYSTEM_MODE_WRITE);
	fchildout = callsystem_fdopen(DATA(self)->stdout_child, CALLSYSTEM_MODE_READ);
	fchilderr = callsystem_fdopen(DATA(self)->stderr_child, CALLSYSTEM_MODE_READ);


	DATA(self)->pid = CALLSYSTEM_ILG_PID;

	LIST_FOREACH(envKeys, i, k,
		IoObject *v;
		IOASSERT(ISSEQ(k), "envKeys must be strings");
		v = IoMap_rawAt(envMap, k);
		IOASSERT(ISSEQ(v), "envValues must be strings");
		callsystem_setenv(&(DATA(self)->env), UTF8CSTRING(k), UTF8CSTRING(v));
	);

	LIST_FOREACH(args, i, arg,
		IOASSERT(ISSEQ(arg), "args must be strings");
		callsystem_argv_pushback(&DATA(self)->args, UTF8CSTRING(arg));
	);


	err = callsystem(CSTRING(command),
		DATA(self)->args,
		DATA(self)->env,


		DATA(self)->stdin_child,
		DATA(self)->stdout_child,
		DATA(self)->stderr_child,

		NULL,
		0,
		&(DATA(self)->pid));


	DATA(self)->needsClose = 1;

	if (err != -1)
	{
		IoObject_setSlot_to_(self, IOSYMBOL("stdin"), IoFile_newWithStream_(IOSTATE, fchildin));
		IoObject_setSlot_to_(self, IOSYMBOL("stdout"), IoFile_newWithStream_(IOSTATE, fchildout));
		IoObject_setSlot_to_(self, IOSYMBOL("stderr"), IoFile_newWithStream_(IOSTATE, fchilderr));


		IoSystemCall_clearPipeDescriptors(self);
	}

	return IONUMBER(err);
}
