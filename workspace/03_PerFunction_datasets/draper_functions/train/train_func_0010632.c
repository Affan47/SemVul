nsslowcert_InitLocks(void)
{
    if (freeListLock == NULL) {
	freeListLock = PZ_NewLock(nssILockRefLock);
	if (freeListLock == NULL) {
	    return SECFailure;
	}
    }
    if (certRefCountLock == NULL) {
	certRefCountLock = PZ_NewLock(nssILockRefLock);
	if (certRefCountLock == NULL) {
	    return SECFailure;
	}
    }
    if (certTrustLock == NULL ) {
	certTrustLock = PZ_NewLock(nssILockCertDB);
	if (certTrustLock == NULL) {
	    return SECFailure;
	}
    }

    return SECSuccess;
}
