read(
    DcmInputStream & inStream,
    const E_TransferSyntax ixfer,
    const E_GrpLenEncoding glenc,
    const Uint32 maxReadLength)
{
    OFCondition l_error =
        DcmOtherByteOtherWord::read(inStream, ixfer, glenc, maxReadLength);

    if (getTransferState() == ERW_ready)
        currentVR = getTag().getEVR();

    return l_error;
}
