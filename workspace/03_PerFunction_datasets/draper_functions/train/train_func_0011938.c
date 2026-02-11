PKIX_PL_Cert_GetSubjectPublicKey(
        PKIX_PL_Cert *cert,
        PKIX_PL_PublicKey **pPublicKey,
        void *plContext)
{
        PKIX_PL_PublicKey *pkixPubKey = NULL;
        SECStatus rv;

        CERTSubjectPublicKeyInfo *from = NULL;
        CERTSubjectPublicKeyInfo *to = NULL;
        SECItem *fromItem = NULL;
        SECItem *toItem = NULL;

        PKIX_ENTER(CERT, "PKIX_PL_Cert_GetSubjectPublicKey");
        PKIX_NULLCHECK_THREE(cert, cert->nssCert, pPublicKey);


        if (cert->publicKey == NULL){

                PKIX_OBJECT_LOCK(cert);

                if (cert->publicKey == NULL){


                        PKIX_CHECK(PKIX_PL_Object_Alloc
                                    (PKIX_PUBLICKEY_TYPE,
                                    sizeof (PKIX_PL_PublicKey),
                                    (PKIX_PL_Object **)&pkixPubKey,
                                    plContext),
                                    PKIX_COULDNOTCREATEOBJECT);


                        pkixPubKey->nssSPKI = NULL;


                        PKIX_CHECK(PKIX_PL_Malloc
                                    (sizeof (CERTSubjectPublicKeyInfo),
                                    (void **)&pkixPubKey->nssSPKI,
                                    plContext),
                                    PKIX_MALLOCFAILED);

                        to = pkixPubKey->nssSPKI;
                        from  = &cert->nssCert->subjectPublicKeyInfo;

                        PKIX_NULLCHECK_TWO(to, from);

                        PKIX_CERT_DEBUG
                                ("\t\tCalling SECOID_CopyAlgorithmID).\n");
                        rv = SECOID_CopyAlgorithmID
                                (NULL, &to->algorithm, &from->algorithm);
                        if (rv != SECSuccess) {
                                PKIX_ERROR(PKIX_SECOIDCOPYALGORITHMIDFAILED);
                        }


                        toItem = &to->subjectPublicKey;
                        fromItem = &from->subjectPublicKey;

                        PKIX_NULLCHECK_TWO(toItem, fromItem);

                        toItem->type = fromItem->type;

                        toItem->data =
                                (unsigned char*) PORT_ZAlloc(fromItem->len);
                        if (!toItem->data){
                                PKIX_ERROR(PKIX_OUTOFMEMORY);
                        }

                        (void) PORT_Memcpy(toItem->data,
                                    fromItem->data,
                                    (fromItem->len + 7)>>3);
                        toItem->len = fromItem->len;


                        cert->publicKey = pkixPubKey;
                }

                PKIX_OBJECT_UNLOCK(cert);
        }

        PKIX_INCREF(cert->publicKey);
        *pPublicKey = cert->publicKey;

cleanup:

        if (PKIX_ERROR_RECEIVED && pkixPubKey){
                PKIX_DECREF(pkixPubKey);
                cert->publicKey = NULL;
        }
        PKIX_RETURN(CERT);
}
