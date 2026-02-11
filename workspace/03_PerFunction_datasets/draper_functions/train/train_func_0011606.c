seqAccessBlast(AjPSeqin seqin)
{
    AjBool retval = ajFalse;
    AjPQuery qry;
    SeqPCdQry qryd;

    ajDebug("seqAccessBlast type %d\n", seqin->Input->Query->QueryType);

    qry  = seqin->Input->Query;
    qryd = qry->QryData;

    if(qry->QueryType == AJQUERY_ALL)
        return seqBlastAll(seqin);


    if(qry->QryData)
    {
        if(!seqCdQryReuse(qry))
            return ajFalse;
    }
    else
    {
        seqin->Input->Single = ajTrue;

        if(!seqCdQryOpen(qry))
        {
            ajErr("seqCdQryOpen failed");

            return ajFalse;
        }

        qryd = qry->QryData;
        ajFilebuffDel(&seqin->Input->Filebuff);
        seqin->Input->Filebuff = ajFilebuffNewNofile();


        if(qry->QueryType == AJQUERY_ENTRY)
        {
            ajDebug("entry fields: %Lu hasacc:%B\n",
                    ajListGetLength(qry->QueryFields), qry->HasAcc);

            if(!seqCdQryEntry(qry))
            {
                ajDebug("BLAST Entry failed\n");
            }
        }

        if(qry->QueryType == AJQUERY_QUERY)
        {
            ajDebug("query fields: %Lu hasacc:%B\n",
                    ajListGetLength(qry->QueryFields), qry->HasAcc);

            if(!seqCdQryQuery(qry))
            {
                ajDebug("BLAST Query failed\n");
            }
        }
    }

    if(ajListGetLength(qry->ResultsList))
    {
        retval = seqBlastQryNext(qry);
        qryd = qry->QryData;

        if(retval)
            seqBlastLoadBuff(seqin);
    }

    if(!ajListGetLength(qry->ResultsList))
    {
        ajFileClose(&qryd->libr);
        ajFileClose(&qryd->libs);
        ajFileClose(&qryd->libt);
        ajFileClose(&qryd->libf);
        seqCdQryClose(qry);

        if((qry->QueryType == AJQUERY_ENTRY) && !seqin->Input->Multi)
        {
            AJFREE(qry->QryData);
            qryd = NULL;
        }
    }

    ajStrAssignS(&seqin->Input->Db, qry->DbName);

    return retval;
}
