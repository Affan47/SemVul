nscFreeAllSlots(int moduleIndex)
{

    SFTKSlot *slot = NULL;
    CK_SLOT_ID slotID;
    int i;

    if (nscSlotList[moduleIndex]) {
	CK_ULONG tmpSlotCount = nscSlotCount[moduleIndex];
	CK_SLOT_ID_PTR tmpSlotList = nscSlotList[moduleIndex];
	PLHashTable *tmpSlotHashTable = nscSlotHashTable[moduleIndex];


	for (i=0; i < (int) tmpSlotCount; i++) {
	    slotID = tmpSlotList[i];
	    (void) NSC_CloseAllSessions(slotID);
	}


	nscSlotList[moduleIndex] = NULL;
	nscSlotCount[moduleIndex] = 0;
	nscSlotHashTable[moduleIndex] = NULL;
	nscSlotListSize[moduleIndex] = 0;

	for (i=0; i < (int) tmpSlotCount; i++) {
	    slotID = tmpSlotList[i];
	    slot = (SFTKSlot *)
			PL_HashTableLookup(tmpSlotHashTable, (void *)slotID);
	    PORT_Assert(slot);
	    if (!slot) continue;
	    SFTK_DestroySlotData(slot);
	    PL_HashTableRemove(tmpSlotHashTable, (void *)slotID);
	}
	PORT_Free(tmpSlotList);
	PL_HashTableDestroy(tmpSlotHashTable);
    }
}
