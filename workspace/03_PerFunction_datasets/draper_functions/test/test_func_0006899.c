acdVarSimpleResolve(const AjPStr var, AjPStr* newvar)
{
    AjPStr attrname = NULL;
    AjPStr result   = NULL;
    AjPStr token    = NULL;
    AjPStr varname  = NULL;
    AjPStr restvar   = NULL;
    AjBool ret = ajTrue;
    AjPStr tmpvar = NULL;

    if(!acdRegVarInit)
        acdRegVarDefine();

    if(ajRegExec(acdRegVarname, var))
    {
        tmpvar = ajStrNewS(*newvar);

	ajRegSubI(acdRegVarname, 2, &token);
	acdVarSplit(token, &varname, &attrname);

	if(!ajStrGetLen(attrname))
	    ajStrAssignC(&attrname, "default");

	if(!acdGetAttr(&result, varname, attrname))
	{
	    acdLog("acdVarSimpleResolve failed to resolve '%S.%S\n",
		   varname, attrname);
            if(ajStrMatchC(attrname, "begin"))
                ajStrAssignC(&result, "0");
            else if(ajStrMatchC(attrname, "end"))
                ajStrAssignC(&result, "0");
            else
                ajStrAssignClear(&result);
	}

	ajRegSubI(acdRegVarname, 1, newvar);
	ajStrAppendS(newvar, result);

	if(ajRegPost(acdRegVarname, &restvar))
	    ajStrAppendS(newvar, restvar);

	acdLog("acdVarSimpleResolve name %S resolved to '%S'\n",
               varname, *newvar);

	if(ajRegExec(acdRegVarname, *newvar))
	    ret = ajFalse;

	else if(ajRegExec(acdRegFunction, *newvar))
	    ret = ajFalse;

        if(!ret)
            ajStrAssignS(newvar, tmpvar);

        ajStrDel(&tmpvar);
    }


    ajStrDel(&token);
    ajStrDel(&attrname);
    ajStrDel(&result);
    ajStrDel(&varname);
    ajStrDel(&restvar);

    return ret;
}
