abiview_drawbase(const char* res, const AjPStr baseN)
{

    AjPRegexp rexp = NULL;
    AjBool draw = ajFalse;
    AjPStr b;
    ajint i;


    b = ajStrNew();
    ajStrAssignSubC(&b,res,0,0);

    for(i=0;i<4;i++)
    {
	rexp = ajRegComp(b);
	if(ajRegExec(rexp,baseN))
	    draw = ajTrue;

	ajRegFree(&rexp);
    }

    ajStrDel(&b);

    return draw;
}
