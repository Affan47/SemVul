read(DcmInputStream &inStream,
                                     const E_TransferSyntax xfer,
                                     const E_GrpLenEncoding glenc,
                                     const Uint32 maxReadLength)
{
    if (getTransferState() == ERW_notInitialized)
        errorFlag = EC_IllegalCall;
    else
    {
        if (getTransferState() != ERW_ready)
        {
            DcmXfer xferSyn(xfer);
            errorFlag = DcmItem::read(inStream, xfer, glenc, maxReadLength);


            offsetInFile = OFstatic_cast(Uint32, fStartPosition) - xferSyn.sizeofTagHeader(getTag().getEVR());
        }

        if (getTransferState() == ERW_ready && DirRecordType == ERT_Private)
        {
            DirRecordType = lookForRecordType();
            if (DirRecordType == ERT_Mrdr)
                numberOfReferences = lookForNumberOfReferences();
        }
    }
    return errorFlag;
}
