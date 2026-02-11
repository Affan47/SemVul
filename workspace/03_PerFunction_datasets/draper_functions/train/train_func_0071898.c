FreeResource(AuID id, RESTYPE skipDeleteFuncType)
{
    int cid;
    ResourcePtr res;
    ResourcePtr *prev, *head;
    int *eltptr;
    int elements;
    Bool gotOne = FALSE;

    if (((cid = CLIENT_ID(id)) < MAXCLIENTS) && clientTable[cid].buckets) {
        head = &clientTable[cid].resources[Hash(cid, id)];
        eltptr = &clientTable[cid].elements;

        prev = head;
        while ((res = *prev)) {
            if (res->id == id) {
                RESTYPE rtype = res->type;
                *prev = res->next;
                elements = --*eltptr;
                if (rtype != skipDeleteFuncType)
                    (*DeleteFuncs[rtype & TypeAuMask]) (res->value,
                                                        res->id);
                xfree(res);
                if (*eltptr != elements)
                    prev = head;
                gotOne = TRUE;
            } else
                prev = &res->next;
        }
    }
    if (!gotOne)
        FatalError("Freeing resource id=%X which isn't there", id);
}
