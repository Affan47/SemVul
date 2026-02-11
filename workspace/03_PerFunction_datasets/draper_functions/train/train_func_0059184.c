insertInLRUList(CachedObject *object)
{
    removeFromLRUList(object);

    assert( object );
    assert( !object->free() );
    assert( object->canDelete() );
    assert( object->allowInLRUList() );

    LRUList* list = getLRUListFor(object);

    CachedObject *&head = list->m_head;

    object->m_next = head;
    if (head)
        head->m_prev = object;
    head = object;

    if (object->m_next == 0)
        list->m_tail = object;

    totalSizeOfLRU += object->size();
}
