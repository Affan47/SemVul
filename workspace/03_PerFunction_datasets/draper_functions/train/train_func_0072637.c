commandList(KDB *handle) {
	KeySet *ks;
	ssize_t ret;
	unsigned long options=0;


	if (argSort)                options |= KDB_O_SORT;
	if (argNoRecursive)         options |= KDB_O_NORECURSIVE;
	if (argAll)                 options |= KDB_O_INACTIVE;
	if (!argValue)              options |= KDB_O_STATONLY;


	if (argFullName)            options |= KDB_O_FULLNAME;
	 options |= KDB_O_HEADER | KDB_O_HIER;

	ks=ksNew(0);

	if (!argKeyName || strcmp(argKeyName, "/") == 0)
	{
		Key *walker=0;
		KeySet *tmp = ksNew(0);


		kdbGet(handle,tmp,0,0);

		if (! argNoRecursive) {

			while ((walker=ksPop(tmp))) {


				KeySet *thisRoot=ksNew(0);

				ret=kdbGet(handle,thisRoot,walker,options | KDB_O_POP);


				ksAppendKey(ks,walker);
				ksAppend(ks,thisRoot);
				ksDel(thisRoot);
			}
		} else ksAppend(ks,tmp);
		ksDel(tmp);
	} else {


		ret=kdbGetByName (handle,ks,argKeyName,options);

		if (ret<0) {

			if (errno==ENOTDIR) {

				Key *key=keyNew(argKeyName,KEY_END);

				if (!key)
				{
					char error[200];

					keyDel(key);
					ksDel(ks);

					sprintf(error,"kdb ls: %s",argKeyName);
					kdbPrintError(error);
					return ret;
				}

				if (argValue)
					ret=kdbGetKey(handle,key);
				else ret=kdbStatKey(handle,key);

				if (ret == 0) ksAppendKey(ks,key);
				else {

					char error[200];

					keyDel(key);
					ksDel(ks);

					sprintf(error,"kdb ls: %s",argKeyName);
					kdbPrintError(error);
					return ret;
				}
				keyDel (key);
			} else {
				char error[200];

				ksDel(ks);

				sprintf(error,"kdb ls: %s",argKeyName);
				kdbPrintError(error);
				return ret;
			}
		}
	}


	if (ksNeedSort (ks)) ksSort (ks);

	if (argXML) ksToStream(ks,stdout,options);
	else if (argShell) listAllKeysForShell(ks);
	else if (argGenerate) ksGenerate(ks,stdout, 0);
	else if (argOutput) ksOutput(ks,stdout, KEY_VALUE|KEY_COMMENT);
	else listAllKeys(ks);

	ksDel(ks);
	return 0;
}
