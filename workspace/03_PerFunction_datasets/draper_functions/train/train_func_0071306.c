DXSetPendingCmd(char *major, char *minor, int (*job)(Private), Private data)
{
    int i;
    PendingCmd *p;
    PendingCmdList *pjl = _dxf_getPendingCmdList();

    if (!pjl){
	if (!job)
	    return OK;
	else
	    if (NULL == (pjl = _dxf_newPendingCmdList()))
		goto error;
    }

    for (i = 0, p = pjl->pendingCmdList;
		i < pjl->pendingCmdListSize; i++, p++)
    {


	if (p->job)
	{
	    if (!strcmp(p->major, major) &&
		   ((minor == NULL && p->minor == NULL) ||
		   !strcmp(p->minor, minor)))
	    {
		if (job)
		{
		    p->job  = job;
		    p->data = (Private)DXReference((Object)data);
		    goto done;
		}
		else
		{
		    DXFree(p->major);
		    DXFree(p->minor);
		    DXDelete((Object)p->data);
		    p->job = NULL;
		    goto done;
		}
	    }
	}
    }

    if (pjl->pendingCmdListSize == pjl->pendingCmdListMax)
	if (! _dxf_growPendingCmdList(pjl))
	    goto error;

    p = pjl->pendingCmdList + pjl->pendingCmdListSize++;

    p->major = DXAllocate(strlen(major) + 1);
    if (! p->major)
    {
	p->minor = NULL;
	goto error;
    }

    strncpy(p->major, major, strlen(major) + 1);

    if (minor)
    {
	p->minor = DXAllocate(strlen(minor) + 1);
	if (! p->minor)
	    goto error;

	strncpy(p->minor, minor, strlen(minor) + 1);
    }
    else
	p->minor = NULL;

    p->job  = job;
    p->data = data;

done:
    _dxf_release_PendingCmdList(pjl);
    return OK;

error:
    _dxf_release_PendingCmdList(pjl);
    return ERROR;
}
