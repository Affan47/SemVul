SFileVerifyArchive(HANDLE hMpq)
{
    MPQ_SIGNATURE_INFO si;
    TMPQArchive * ha = (TMPQArchive *)hMpq;


    if(!IsValidMpqHandle(ha))
        return ERROR_VERIFY_FAILED;


    memset(&si, 0, sizeof(MPQ_SIGNATURE_INFO));
    if(!QueryMpqSignatureInfo(ha, &si))
        return ERROR_VERIFY_FAILED;


    switch(si.nSignatureType)
    {
        case SIGNATURE_TYPE_NONE:
            return ERROR_NO_SIGNATURE;

        case SIGNATURE_TYPE_WEAK:
            return VerifyWeakSignature(ha, &si);

        case SIGNATURE_TYPE_STRONG:
            return VerifyStrongSignature(ha, &si);
    }

    return ERROR_VERIFY_FAILED;
}
