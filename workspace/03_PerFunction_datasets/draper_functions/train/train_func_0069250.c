acdReadKeywords(void)
{
    AjPTable ret = ajTablestrNewCase(50);

    AjPFile keyFile    = NULL;
    AjPStr keyFName    = NULL;
    AjPStr keyRoot     = NULL;
    AjPStr keyRootInst = NULL;
    AjPStr keyPack     = NULL;
    AjPStr keyLine     = NULL;
    AjPRegexp keyxp    = NULL;
    AjPStr keyName     = NULL;
    AjPStr keyDesc     = NULL;

    if(!acdGrpTable)
	acdGrpTable = acdReadGroups();

    ajStrAssignS(&keyPack, ajNamValuePackage());
    ajStrAssignS(&keyRootInst, ajNamValueInstalldir());
    ajDirnameFix(&keyRootInst);

    if(ajNamGetValueC("acdroot", &keyRoot))
    {
	ajDirnameFix(&keyRoot);
	ajFmtPrintS(&keyFName, "%Skeywords.standard", keyRoot);
	keyFile = ajFileNewInNameS(keyFName);
	acdLog("Keyword file in acdroot: '%S'\n", keyFName);
    }
    else
    {
	ajFmtPrintS(&keyFName, "%Sshare/%S/acd/keywords.standard",
		    keyRootInst, keyPack);
	acdLog("Keyword file installed: '%S'\n", keyFName);
	keyFile = ajFileNewInNameS(keyFName);

	if(!keyFile)
	{
	    acdLog("keyword file '%S' not opened\n", keyFName);
	    ajStrAssignS(&keyRoot, ajNamValueRootdir());
	    ajDirnameFix(&keyRoot);
	    ajFmtPrintS(&keyFName, "%Sacd/keywords.standard", keyRoot);
	    acdLog("Keywords file from source dir: '%S'\n", keyFName);
	    keyFile = ajFileNewInNameS(keyFName);
	}
    }

    if(!keyFile)
	ajDie("Keyword file %S not found", keyFName);
    else
	acdLog("Keyword file %F used\n", keyFile);

    keyxp = ajRegCompC("([^ ]+) +([^ ].*)");
    while(keyFile && ajReadlineTrim(keyFile, &keyLine))
    {
	if(ajStrCutComments(&keyLine))
	{
	    ajStrRemoveWhiteExcess(&keyLine);

	    if(ajRegExec(keyxp, keyLine))
	    {
		ajRegSubI(keyxp, 1, &keyName);
		ajRegSubI(keyxp, 2, &keyDesc);
		ajStrExchangeKK(&keyName, '_', ' ');

		if(ajTableFetchS(acdGrpTable, keyName))
		    ajWarn("Keyword %S in file %S is a known group",
			   keyName, keyFName);
		if(ajTablePut(ret, keyName, keyDesc))
		    ajWarn("Duplicate keyword in file %S",
			   keyFName);
		keyName = NULL;
		keyDesc = NULL;
	    }
	    else
		ajErr("Bad record in file %S:\n%S",
		      keyFName, keyLine);
	}
    }

    ajFileClose(&keyFile);

    ajStrDel(&keyFName);
    ajStrDel(&keyRoot);
    ajStrDel(&keyRootInst);
    ajStrDel(&keyPack);
    ajStrDel(&keyLine);
    ajStrDel(&keyName);
    ajStrDel(&keyDesc);

    ajRegFree(&keyxp);

    return ret;
}
