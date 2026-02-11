crmf_get_encvalue_algid(SECAlgorithmID *srcAlg)
{
    SECStatus       rv;
    SECAlgorithmID *newAlgID;

    if (srcAlg == NULL) {
        return NULL;
    }
    rv = crmf_copy_encryptedvalue_secalg(NULL, srcAlg, &newAlgID);
    if (rv != SECSuccess) {
        return NULL;
    }
    return newAlgID;
}
