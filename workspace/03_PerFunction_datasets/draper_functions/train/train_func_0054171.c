ajDatafileNewOutNameS(const AjPStr name)
{
    AjPFile fnew = NULL;

    if(!ajStrGetLen(name))
        return NULL;

    if(ajNamGetValueC("DATA", &filedataNameDataTmp))
    {

	if(!ajDirnameFixExists(&filedataNameDataTmp))
	{
	    ajFatal("%S_DATA directory not found: %S\n",
		    ajNamValuePackage(), filedataNameDataTmp);
	}

	ajStrAppendS(&filedataNameDataTmp,name);

	if(!(fnew = ajFileNewOutNameS(filedataNameDataTmp)))
	    ajFatal("Cannot write to file %S\n",filedataNameDataTmp);

	ajStrDelStatic(&filedataNameDataTmp);

	return fnew;
    }


    ajStrAssignS(&filedataNameDataTmp, ajNamValueInstalldir());

    if(ajStrGetLen(filedataNameDataTmp))
    {

	ajDirnameFix(&filedataNameDataTmp);
	ajStrAppendC(&filedataNameDataTmp,"share/");
	ajStrAppendS(&filedataNameDataTmp,ajNamValuePackage());
	ajStrAppendC(&filedataNameDataTmp,"/data/");


	if(ajDirnameFixExists(&filedataNameDataTmp))
	{
	    ajStrAppendS(&filedataNameDataTmp,name);

	    if(!(fnew = ajFileNewOutNameS(filedataNameDataTmp)))
		ajFatal("Cannot write to file %S\n",filedataNameDataTmp);

	    ajStrDelStatic(&filedataNameDataTmp);

	    return fnew;
	}
    }


    ajStrAssignS(&filedataNameDataTmp, ajNamValueRootdir());

    if(ajStrGetLen(filedataNameDataTmp))
    {
	ajStrAppendC(&filedataNameDataTmp,"/data/");

	if(!ajDirnameFixExists(&filedataNameDataTmp))
	    ajFatal("Not installed, and source data directory not found: %S\n",
		    filedataNameDataTmp);

	ajStrAppendS(&filedataNameDataTmp,name);

	if(!(fnew = ajFileNewOutNameS(filedataNameDataTmp)))
	    ajFatal("Cannot write to file %S\n",filedataNameDataTmp);

	ajStrDelStatic(&filedataNameDataTmp);

	return fnew;
    }


    ajFatal("No install or source data directory, and %S_DATA not defined\n",
	    ajNamValuePackage());
    ajStrDelStatic(&filedataNameDataTmp);

    return NULL;
}
