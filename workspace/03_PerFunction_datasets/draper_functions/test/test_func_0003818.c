textAccessApp(AjPTextin textin)
{
    static AjPStr pipename = NULL;
    AjPQuery qry;
    AjIList iter = NULL;
    AjPQueryField field = NULL;

    qry = textin->Query;

    if(!ajStrGetLen(qry->Application))
    {
	ajErr("APP access: application not defined for %S", qry->DbName);

	return ajFalse;
    }

    ajDebug("textAccessApp '%S' dbname '%S'\n", qry->Application, qry->DbName);

    if(ajStrMatchWildC(qry->Application, "*%s*"))
    {
        if(ajListGetLength(qry->QueryFields))
        {
            iter = ajListIterNewread(qry->QueryFields);
            while(!ajListIterDone(iter))
            {
                field = ajListIterGet(iter);
                if(ajStrMatchC(field->Field, "id"))
                    ajFmtPrintS(&pipename, ajStrGetPtr(qry->Application),
                                ajStrGetPtr(field->Wildquery));
                else if(qry->HasAcc && ajStrMatchC(field->Field, "acc"))
                    ajFmtPrintS(&pipename, ajStrGetPtr(qry->Application),
                                ajStrGetPtr(field->Wildquery));
                else
                    ajFmtPrintS(&pipename, ajStrGetPtr(qry->Application),
                                ajStrGetPtr(field->Wildquery));
            }
            ajListIterDel(&iter);
        }
        else
            ajFmtPrintS(&pipename, ajStrGetPtr(qry->Application),
                        "*");

	ajStrAppendC(&pipename, " |");
    }
    else
    {
        if(ajListGetLength(qry->QueryFields))
        {
            iter = ajListIterNewread(qry->QueryFields);
            while(!ajListIterDone(iter))
            {
                field = ajListIterGet(iter);
                if(ajStrMatchC(field->Field, "id"))
                    ajFmtPrintS(&pipename, "%S %S:%S|",
                                qry->Application, qry->DbName,
                                field->Wildquery);
                else if(qry->HasAcc && ajStrMatchC(field->Field, "acc"))
                    ajFmtPrintS(&pipename, "%S %S:%S|",
                                qry->Application, qry->DbName,
                                field->Wildquery);
                else
                    ajFmtPrintS(&pipename, "%S %S:%S|",
                                qry->Application, qry->DbName,
                                field->Wildquery);
            }
            ajListIterDel(&iter);
        }
        else
	    ajFmtPrintS(&pipename, "%S %S:*|",
			qry->Application, qry->DbName);
    }

    if(!ajStrGetLen(pipename))
    {
	ajErr("APP access: bad query format");

	return ajFalse;
    }


    ajFilebuffDel(&textin->Filebuff);
    textin->Filebuff = ajFilebuffNewNameS(pipename);

    if(!textin->Filebuff)
    {
	ajErr("unable to open file '%S'", pipename);
	ajStrDel(&pipename);

	return ajFalse;
    }

    ajStrAssignS(&textin->Db, qry->DbName);

    ajStrDel(&pipename);

    if(!qry->CaseId)
	qry->QryDone = ajTrue;

    return ajTrue;
}
