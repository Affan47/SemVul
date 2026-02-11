CMMF_POPODecKeyChallContDecryptChallenge(CMMFPOPODecKeyChallContent *inChalCont,
					 int                         inIndex,
					 SECKEYPrivateKey           *inPrivKey)
{
    CMMFChallenge  *challenge;
    SECItem        *decryptedRand=NULL;
    PLArenaPool    *poolp  = NULL;
    SECAlgorithmID *owf;
    SECStatus       rv     = SECFailure;
    SECOidTag       tag;
    CMMFRand        randStr;
    SECItem         hashItem;
    unsigned char   hash[HASH_LENGTH_MAX];

    PORT_Assert(inChalCont != NULL && inPrivKey != NULL);
    if (inChalCont == NULL || inIndex <0 || inIndex > inChalCont->numChallenges
	|| inPrivKey == NULL){
        return SECFailure;
    }

    poolp = PORT_NewArena(CRMF_DEFAULT_ARENA_SIZE);
    if (poolp == NULL) {
        goto loser;
    }

    challenge = inChalCont->challenges[inIndex];
    decryptedRand = SECITEM_AllocItem(poolp, NULL, challenge->challenge.len);
    if (decryptedRand == NULL) {
        goto loser;
    }
    rv = PK11_PrivDecryptPKCS1(inPrivKey, decryptedRand->data,
    			&decryptedRand->len, decryptedRand->len,
			challenge->challenge.data, challenge->challenge.len);
    if (rv != SECSuccess) {
        goto loser;
    }

    rv = SEC_ASN1DecodeItem(poolp, &randStr, CMMFRandTemplate,
			    decryptedRand);
    if (rv != SECSuccess) {
        goto loser;
    }
    rv = SECFailure;


    owf = cmmf_get_owf(inChalCont, inIndex);
    if (owf == NULL) {

        goto loser;
    }

    tag = SECOID_FindOIDTag(&owf->algorithm);
    hashItem.len = HASH_ResultLenByOidTag(tag);
    if (!hashItem.len)
        goto loser;

    rv = PK11_HashBuf(tag, hash, randStr.integer.data, randStr.integer.len);
    if (rv != SECSuccess) {
        goto loser;
    }
    hashItem.data = hash;
    if (SECITEM_CompareItem(&hashItem, &challenge->witness) != SECEqual) {


	PORT_SetError(SEC_ERROR_BAD_DATA);
        rv = SECFailure;
	goto loser;
    }
    rv = PK11_HashBuf(tag, hash, challenge->senderDER.data,
		      challenge->senderDER.len);
    if (rv != SECSuccess) {
        goto loser;
    }
    if (SECITEM_CompareItem(&hashItem, &randStr.senderHash) != SECEqual) {


	PORT_SetError(SEC_ERROR_BAD_DATA);
        rv = SECFailure;
	goto loser;
    }

    rv = SECITEM_CopyItem(inChalCont->poolp, &challenge->randomNumber,
			  &randStr.integer);
 loser:
    if (poolp) {
    	PORT_FreeArena(poolp, PR_FALSE);
    }
    return rv;
}
