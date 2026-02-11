acdDataFilename(AjPStr* infname,
			      const AjPStr name, const AjPStr ext,
			      AjBool nullok)
{
    AjBool ret = ajTrue;

    if(ajStrGetLen(name))
	ajStrAssignS(infname, name);
    else if(!nullok)
	ajStrAssignS(infname, acdProgram);
    else
	ajStrAssignClear(infname);

    if(ajStrGetLen(ext))
	ajFilenameReplaceExtS(infname, ext);
    else
	if (!nullok)
	    ajFilenameReplaceExtC(infname, "dat");

    return ret;
}
