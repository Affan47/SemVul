feattableWriteRefseqp(const AjPFeattable thys, AjPFile file)
{
    AjIList    iter     = NULL;
    AjPFeature gf       = NULL;


    if(!file)
	return ajFalse;

    if(ajFeattableIsNuc(thys))
	return ajFalse;


    ajFmtPrintF(file, "FEATURES             Location/Qualifiers\n");


    ajListSort(thys->Features, &ajFeatCompByGroup);

    iter = ajListIterNewread(thys->Features);

    while(!ajListIterDone(iter))
    {
        gf = ajListIterGet(iter);

        featWriteRefseqp(gf, file, thys->Seqid);
    }

    ajListIterDel(&iter);


    return ajTrue;
}
