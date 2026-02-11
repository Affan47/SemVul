closeDatabase(IDB_HANDLE ** handle)
{
    CONDITION cond = 0;

    cond = IDB_Close(handle);
    if (cond != IDB_NORMAL) {
	COND_DumpConditions();
	THR_Shutdown();
	exit(1);
    }
}
