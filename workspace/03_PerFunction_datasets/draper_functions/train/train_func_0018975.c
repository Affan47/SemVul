PK11_LoadSlotList(PK11SlotInfo *slot, PK11PreSlotInfo *psi, int count)
{
    int i;

    for (i=0; i < count; i++) {
	if (psi[i].slotID == slot->slotID)
	    break;
    }

    if (i == count) return;

    slot->defaultFlags = psi[i].defaultFlags;
    slot->askpw = psi[i].askpw;
    slot->timeout = psi[i].timeout;
    slot->hasRootCerts = psi[i].hasRootCerts;


    if (slot->disabled) return;


    if (slot->defaultFlags & PK11_DISABLE_FLAG) {
	slot->disabled = PR_TRUE;
	slot->reason = PK11_DIS_USER_SELECTED;

	return;
    }

    for (i=0; i < num_pk11_default_mechanisms; i++) {
	if (slot->defaultFlags & PK11_DefaultArray[i].flag) {
	    CK_MECHANISM_TYPE mechanism = PK11_DefaultArray[i].mechanism;
	    PK11SlotList *slotList = PK11_GetSlotList(mechanism);

	    if (slotList) PK11_AddSlotToList(slotList,slot,PR_FALSE);
	}
    }

    return;
}
