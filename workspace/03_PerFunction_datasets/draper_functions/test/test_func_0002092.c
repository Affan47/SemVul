PK11_GetNextSafe(PK11SlotList *list, PK11SlotListElement *le, PRBool restart)
{
    PK11SlotListElement *new_le;
    PZ_Lock(list->lock);
    new_le = le->next;
    if (le->next == NULL) {


	if ((le->prev == NULL) && restart &&  (list->head != le)) {
	    new_le = list->head;
	}
    }
    if (new_le) new_le->refCount++;
    PZ_Unlock(list->lock);
    PK11_FreeSlotListElement(list,le);
    return new_le;
}
