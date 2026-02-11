AddVOMSACSeqExtension(void* extHandle, char* vomsacseq, int length) {
    SECStatus rv = SECFailure;
    SECOidData* oid = NULL;
    SECOidTag tag;

    tag = tag_vomsacseq;
    oid = SECOID_FindOIDByTag(tag);

    if(vomsacseq != NULL) {
      SECItem encodedValue;

      encodedValue.data = (unsigned char*)vomsacseq;
      encodedValue.len = length;
      rv = CERT_AddExtension(extHandle, tag, &encodedValue,
                               PR_FALSE, PR_TRUE);
    }

    return (rv);
  }
