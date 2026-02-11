ajFeattableNewFtable(const AjPFeattable orig)
{
    AjPFeattable ret = NULL;
    AjIList iter;
    AjPFeature featorig;
    AjPFeature feat = NULL;

    if(!orig)
	return NULL;

    ret = featTableNew();

    ajStrAssignS(&ret->Seqid, orig->Seqid);
    ajStrAssignS(&ret->Type, orig->Type);

    ajStrAssignS(&ret->Formatstr, orig->Formatstr);
    ret->Format    = orig->Format;

    ret->Groups    = orig->Groups;
    ret->Start     = orig->Start;
    ret->End       = orig->End;
    ret->Len       = orig->Len;
    ret->Offset    = orig->Offset;
    ret->Rev       = orig->Rev;
    ret->Reversed  = orig->Reversed;
    ret->Trimmed   = orig->Trimmed;
    ret->Circular  = orig->Circular;

    ret->Fpos      = orig->Fpos;

    ajStrAssignS(&ret->Db, orig->Db);
    ajStrAssignS(&ret->Setdb, orig->Setdb);
    ajStrAssignS(&ret->Full, orig->Full);
    ajStrAssignS(&ret->Qry, orig->Qry);
    ajStrAssignS(&ret->Filename, orig->Filename);
    ajStrAssignS(&ret->TextPtr, orig->TextPtr);

    iter = ajListIterNewread(orig->Features);

    while(!ajListIterDone(iter))
    {
	featorig = ajListIterGet(iter);
	feat = ajFeatNewFeat(featorig);
	ajFeattableAdd(ret, feat);
    }

    ajListIterDel(&iter);

    return ret;
}
