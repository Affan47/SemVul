ajSeqoutCloseEmpty(AjPSeqout seqout)
{

    ajDebug("ajSeqoutCloseEmpty '%F'\n", seqout->File);

    if(seqOutFormat[seqout->Format].Save)
    {

	(*seqOutFormat[seqout->Format].Write)(seqout);
    }

    if(seqout->Cleanup)
        (*seqout->Cleanup)(seqout);
    seqout->Cleanup = NULL;

    if(seqout->File && seqout->Count)
        ajWarn("Not empty file: %d sequence(s) written to output file '%F'",
               seqout->Count, seqout->File);

    if(seqout->Knownfile)
	seqout->File = NULL;
    else
	ajFileClose(&seqout->File);

    return;
}
