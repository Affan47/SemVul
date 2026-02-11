seqBlastAll(AjPSeqin seqin)
{
    AjPQuery qry;
    SeqPCdQry qryd;

    qry  = seqin->Input->Query;
    qryd = qry->QryData;

    ajDebug("seqBlastAll\n");

    if(!qry->QryData)
    {
        ajDebug("seqBlastAll initialising\n");
        seqin->Input->Single = ajTrue;

        if(!seqBlastOpen(qry, ajTrue))
            ajFatal("seqBlastAll failed");

        qryd = qry->QryData;
        ajFilebuffDel(&seqin->Input->Filebuff);
        seqin->Input->Filebuff = ajFilebuffNewNofile();
        qryd->idnum = 0;
    }
    else
        qryd = qry->QryData;

    if(!qryd->libr)
    {
        ajDebug("seqBlastAll finished\n");
        seqBlastQryClose(qry);

        return ajFalse;
    }

    if(!seqBlastLoadBuff(seqin))
    {
        if(!seqBlastOpen(qry, ajTrue))
        {
            seqBlastQryClose(qry);

            return ajFalse;
        }

        qryd = qry->QryData;
        qryd->idnum = 0;

        if(!qryd->libr)
        {
            seqBlastQryClose(qry);
            ajDebug("seqBlastAll finished\n");

            return ajFalse;
        }

        if(!seqBlastLoadBuff(seqin))
        {
            seqBlastQryClose(qry);

            return ajFalse;
        }
    }

    qryd->idnum++;
    ajStrAssignS(&seqin->Input->Db, qry->DbName);

    if(!qry->CaseId)
        qry->QryDone = ajTrue;

    return ajTrue;
}
