sdb_getObjectId(SDB *sdb)
{
    CK_OBJECT_HANDLE candidate;
    static CK_OBJECT_HANDLE next_obj = CK_INVALID_HANDLE;
    int count;


    if (next_obj == CK_INVALID_HANDLE) {
        PRTime time;
	time = PR_Now();

	next_obj = (CK_OBJECT_HANDLE)(time & 0x3fffffffL);
    }
    candidate = next_obj++;

    for (count = 0; count < 0x40000000; count++, candidate = next_obj++) {

	candidate &= 0x3fffffff;

	if (candidate == CK_INVALID_HANDLE) {
	    continue;
	}

	if (!sdb_objectExists(sdb, candidate)) {

	    return candidate;
	}
    }


    return CK_INVALID_HANDLE;
}
