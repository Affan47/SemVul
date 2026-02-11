ajResourceinRead(AjPResourcein resourcein, AjPResource resource)
{
    AjBool ret       = ajFalse;
    AjPQueryList node = NULL;
    AjBool listdata  = ajFalse;

    if(resourcein->Input->Filebuff)
    {

	ret = resourceinRead(resourcein, resource);
    }
    else
    {

	if(ajListGetLength(resourcein->Input->List))
	{
	    listdata = ajTrue;
	    ajListPop(resourcein->Input->List, (void**) &node);

	    ajResourceinQryS(resourcein, node->Qry);

            resourceinQryRestore(resourcein, node);

	    ajStrDel(&node->Qry);
	    ajStrDel(&node->Formatstr);
	    AJFREE(node);

	    if(!resourceinQryProcess(resourcein, resource) &&
               !ajListGetLength(resourcein->Input->List))
		return ajFalse;

	    ret = resourceinRead(resourcein, resource);
	}
	else
	{

	    if(!resourceinQryProcess(resourcein, resource) &&
               !ajListGetLength(resourcein->Input->List))
		return ajFalse;

	    if(ajListGetLength(resourcein->Input->List))
		listdata = ajTrue;

	    ret = resourceinRead(resourcein, resource);
	}
    }


    while(!ret && ajListGetLength(resourcein->Input->List))
    {

        if(listdata)
	    ajErr("Failed to read data data '%S'",
                  resourcein->Input->Qry);

	listdata = ajTrue;
	ajListPop(resourcein->Input->List,(void**) &node);
	ajResourceinQryS(resourcein, node->Qry);

	resourceinQryRestore(resourcein, node);

	ajStrDel(&node->Qry);
	ajStrDel(&node->Formatstr);
	AJFREE(node);

	if(!resourceinQryProcess(resourcein, resource))
	    continue;

	ret = resourceinRead(resourcein, resource);
    }

    if(!ret)
    {
	if(listdata)
	    ajErr("Failed to read data data '%S'",
                  resourcein->Input->Qry);

	return ajFalse;
    }


    resourceDefine(resource, resourcein);

    return ajTrue;
}
