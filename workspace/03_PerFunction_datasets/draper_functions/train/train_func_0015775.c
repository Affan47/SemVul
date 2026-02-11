computeGroupLengthAndPadding(const E_GrpLenEncoding glenc,
                                                             const E_PaddingEncoding padenc,
                                                             const E_TransferSyntax xfer,
                                                             const E_EncodingType enctype,
                                                             const Uint32 padlen,
                                                             const Uint32 subPadlen,
                                                             Uint32 instanceLength)
{
    OFCondition l_error = EC_Normal;

    if (!itemList->empty())
    {
        itemList->seek(ELP_first);
        do {
            DcmItem *dO = OFstatic_cast(DcmItem *, itemList->get());
            l_error = dO->computeGroupLengthAndPadding
                (glenc, padenc, xfer, enctype, padlen, subPadlen, instanceLength);
        } while (l_error.good() && itemList->seek(ELP_next));
    }
    return l_error;
}
