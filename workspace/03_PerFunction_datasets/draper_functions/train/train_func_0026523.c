writeSignatureFormat(DcmOutputStream &outStream,
                                                     const E_TransferSyntax oxfer,
                                                     const E_EncodingType enctype,
                                                     DcmWriteCache *wcache)
{
    if (getTransferState() == ERW_notInitialized)
        errorFlag = EC_IllegalCall;
    else
    {
        errorFlag = outStream.status();
        if (errorFlag.good() && (getTransferState() != ERW_ready))
        {
            if (getTransferState() == ERW_init)
            {


                if ((outStream.avail() >= DCM_TagInfoLength) ||
                    (outStream.avail() >= getTagAndLengthSize(oxfer)))
                {
                    if (enctype == EET_ExplicitLength)
                        setLengthField(getLength(oxfer, enctype));
                    else
                        setLengthField(DCM_UndefinedLength);
                    errorFlag = writeTagAndVR(outStream, getTag(), getVR(), oxfer);

                    if (errorFlag.good())
                    {
                        setTransferState(ERW_inWork);
                        itemList->seek(ELP_first);
                    }
                } else
                    errorFlag = EC_StreamNotifyClient;
            }
            if (getTransferState() == ERW_inWork)
            {


                if (!itemList->empty() && (itemList->get() != NULL))
                {
                    DcmObject *dO;
                    do {
                        dO = itemList->get();
                        if (dO->transferState() != ERW_ready)
                            errorFlag = dO->writeSignatureFormat(outStream, oxfer, enctype, wcache);
                    } while (errorFlag.good() && itemList->seek(ELP_next));
                }
                if (errorFlag.good())
                {
                    setTransferState(ERW_ready);

                    if (outStream.avail() >= 4)
                    {

                        DcmTag delim(DCM_SequenceDelimitationItem);
                        errorFlag = writeTag(outStream, delim, oxfer);
                    } else {


                        setTransferState(ERW_inWork);
                        errorFlag = EC_StreamNotifyClient;
                    }
                }
            }
        }
    }
    return errorFlag;
}
