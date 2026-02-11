PK11_GetAttributes(PLArenaPool *arena,PK11SlotInfo *slot,
			CK_OBJECT_HANDLE obj,CK_ATTRIBUTE *attr, int count)
{
    int i;

    void *mark = NULL;
    CK_RV crv;
    PORT_Assert(slot->session != CK_INVALID_SESSION);
    if (slot->session == CK_INVALID_SESSION)
	return CKR_SESSION_HANDLE_INVALID;


    PK11_EnterSlotMonitor(slot);
    crv = PK11_GETTAB(slot)->C_GetAttributeValue(slot->session,obj,attr,count);
    if (crv != CKR_OK) {
	PK11_ExitSlotMonitor(slot);
	return crv;
    }

    if (arena) {
    	mark = PORT_ArenaMark(arena);
	if (mark == NULL) return CKR_HOST_MEMORY;
    }


    for (i=0; i < count; i++) {
	if (attr[i].ulValueLen == 0)
	    continue;
	if (arena) {
	    attr[i].pValue = PORT_ArenaAlloc(arena,attr[i].ulValueLen);
	    if (attr[i].pValue == NULL) {

		PORT_ArenaRelease(arena,mark);
		PK11_ExitSlotMonitor(slot);
		return CKR_HOST_MEMORY;
	    }
	} else {
	    attr[i].pValue = PORT_Alloc(attr[i].ulValueLen);
	    if (attr[i].pValue == NULL) {


		int j;
		for (j= 0; j < i; j++) {
		    PORT_Free(attr[j].pValue);

		    attr[j].pValue = NULL;
		}
		PK11_ExitSlotMonitor(slot);
		return CKR_HOST_MEMORY;
	    }
	}
    }


    crv = PK11_GETTAB(slot)->C_GetAttributeValue(slot->session,obj,attr,count);
    PK11_ExitSlotMonitor(slot);
    if (crv != CKR_OK) {
	if (arena) {
	    PORT_ArenaRelease(arena,mark);
	} else {
	    for (i= 0; i < count; i++) {
		PORT_Free(attr[i].pValue);

		attr[i].pValue = NULL;
	    }
	}
    } else if (arena && mark) {
	PORT_ArenaUnmark(arena,mark);
    }
    return crv;
}
