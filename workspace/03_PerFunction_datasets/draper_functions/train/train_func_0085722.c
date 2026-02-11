CRMF_POPOPrivKeyGetThisMessage(CRMFPOPOPrivKey  *inKey,
			       SECItem          *destString)
{
    PORT_Assert(inKey != NULL);
    if (inKey == NULL           ||
	inKey->messageChoice != crmfThisMessage) {
        return SECFailure;
    }

    return crmf_make_bitstring_copy(NULL, destString,
				    &inKey->message.thisMessage);
}
