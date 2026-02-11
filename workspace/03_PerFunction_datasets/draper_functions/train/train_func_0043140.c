nssSlot_CreateFromPK11SlotInfo(NSSTrustDomain *td, PK11SlotInfo *nss3slot)
{
    NSSSlot *rvSlot;
    NSSArena *arena;
    arena = nssArena_Create();
    if (!arena) {
	return NULL;
    }
    rvSlot = nss_ZNEW(arena, NSSSlot);
    if (!rvSlot) {
	nssArena_Destroy(arena);
	return NULL;
    }
    rvSlot->base.refCount = 1;
    rvSlot->base.lock = PZ_NewLock(nssILockOther);
    rvSlot->base.arena = arena;
    rvSlot->pk11slot = nss3slot;
    rvSlot->epv = nss3slot->functionList;
    rvSlot->slotID = nss3slot->slotID;

    rvSlot->base.name = nssUTF8_Duplicate(nss3slot->slot_name,td->arena);
    rvSlot->lock = (nss3slot->isThreadSafe) ? NULL : nss3slot->sessionLock;
    return rvSlot;
}
