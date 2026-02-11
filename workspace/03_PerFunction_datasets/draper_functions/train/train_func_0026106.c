ajCallRegisterOld(const char *name, CallFunc func)
{
    const void *rec;
    char* keyname = NULL;
    ajuint *i;

    if(!oldcallTable)
    {
	oldcallTable = ajTablecharNew(50);
	oldcallCount = ajTablecharNew(50);
    }

    rec = ajTableFetchC(oldcallTable, name);

    if(!rec)
    {
	keyname = ajCharNewC(name);
	ajTablePut(oldcallTable, keyname, (void *) func);
	keyname = ajCharNewC(name);
        AJNEW0(i);
	ajTablePut(oldcallCount, keyname, i);
    }

    return;
}
