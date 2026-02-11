sftk_searchTokenList(SFTKSlot *slot, SFTKSearchResults *search,
                        CK_ATTRIBUTE *pTemplate, CK_ULONG ulCount,
                        PRBool *tokenOnly, PRBool isLoggedIn)
{
    CK_RV crv = CKR_OK;
    CK_RV crv2;
    PRBool searchCertDB;
    PRBool searchKeyDB;

    sftk_pruneSearch(pTemplate, ulCount, &searchCertDB, &searchKeyDB);

    if (searchCertDB) {
	SFTKDBHandle *certHandle = sftk_getCertDB(slot);
	crv = sftk_searchDatabase(certHandle, search, pTemplate, ulCount);
	crv2 = sftk_emailhack(slot, certHandle, search, pTemplate, ulCount);
	if (crv == CKR_OK) crv = crv2;
	sftk_freeDB(certHandle);
    }

    if (crv == CKR_OK && isLoggedIn && searchKeyDB) {
	SFTKDBHandle *keyHandle = sftk_getKeyDB(slot);
    	crv = sftk_searchDatabase(keyHandle, search, pTemplate, ulCount);
    	sftk_freeDB(keyHandle);
    }
    return crv;
}
