ajVarloadMore(AjPVarload thys, AjPVar *Pvar)
{
    AjPVarin  varin = thys->Varin;
    AjPTextin input = varin->Input;

    ajDebug("ajVarloadMore count:%u dataread: %B datadone: %B"
           " loading varload: %B varin: %B\n",
            thys->Count, input->Dataread, input->Datadone,
            thys->Loading, varin->Loading);

    if(input->Datadone)
    {
        input->Dataread = ajFalse;
        input->Datadone = ajFalse;
        ajDebug("ajVarloadMore done\n");
        return ajFalse;
    }

    if(!varin->Loading)
    {
        varin->Loading = ajTrue;
        thys->Count++;

	*Pvar = thys->Var;
	thys->Returned = ajTrue;

	ajDebug("ajVarloadMore initial\n");

	return ajTrue;
    }

    if(ajVarinLoad(thys->Varin, thys->Var))
    {
        *Pvar = thys->Var;
	thys->Returned = ajTrue;

	ajDebug("ajVarloadMore success\n");

	return ajTrue;
    }

    *Pvar = NULL;
    thys->Returned = ajFalse;

    ajDebug("ajVarloadMore failed to read\n");

    return ajFalse;
}
