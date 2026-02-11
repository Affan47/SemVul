CRMF_EncryptedKeyGetEncryptedValue(CRMFEncryptedKey *inEncrKey)
{
    CRMFEncryptedValue *newEncrValue = NULL;
    SECStatus           rv;

    PORT_Assert(inEncrKey != NULL);
    if (inEncrKey == NULL ||
	CRMF_EncryptedKeyGetChoice(inEncrKey) != crmfEncryptedValueChoice) {
        goto loser;
    }
    newEncrValue = PORT_ZNew(CRMFEncryptedValue);
    if (newEncrValue == NULL) {
        goto loser;
    }
    rv = crmf_copy_encryptedvalue(NULL, &inEncrKey->value.encryptedValue,
				  newEncrValue);
    if (rv != SECSuccess) {
        goto loser;
    }
    return newEncrValue;
 loser:
    if (newEncrValue != NULL) {
        CRMF_DestroyEncryptedValue(newEncrValue);
    }
    return NULL;
}
