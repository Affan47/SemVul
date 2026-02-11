calcElementLength(const E_TransferSyntax xfer,
                                     const E_EncodingType enctype)
{
    DcmXfer xferSyn(xfer);
    const Uint32 headerLength = xferSyn.sizeofTagHeader(getVR());
    const Uint32 elemLength = getLength(xfer, enctype);
    if (OFStandard::check32BitAddOverflow(headerLength, elemLength))
      return DCM_UndefinedLength;
    else
      return headerLength + elemLength;
}
