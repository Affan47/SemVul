_pilPAFInsertAfter(PilList *list, const char *key, const char *name,
                   PilPAFType type, const void *value, const char *comment)
{

    PilPAFRecord *record;
    PilListNode *node, *position;


    position = pilListLookup(list, key, _pilPAFRecordCompare);
    if (!position)
        return 1;

    record = _pilPAFRecordCreate(name, type, value, comment);
    if (!record)
        return 1;

    node = newPilListNode(record);
    if (!node)
        return 1;

    pilListInsertAfter(list, position, node);

    return 0;

}
