sftk_closePeer(PRBool isFIPS)
{
    CK_SLOT_ID slotID = isFIPS ? PRIVATE_KEY_SLOT_ID: FIPS_SLOT_ID;
    SFTKSlot *slot;
    int moduleIndex = isFIPS? NSC_NON_FIPS_MODULE : NSC_FIPS_MODULE;
    PLHashTable *tmpSlotHashTable = nscSlotHashTable[moduleIndex];

    slot = (SFTKSlot *) PL_HashTableLookup(tmpSlotHashTable, (void *)slotID);
    if (slot == NULL) {
	return;
    }
    sftk_DBShutdown(slot);
    return;
}
