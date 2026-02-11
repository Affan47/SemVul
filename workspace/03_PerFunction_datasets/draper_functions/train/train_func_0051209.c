removeDirect(const Identifier& propertyName)
{
    bool isArrayIndex;
    unsigned i = propertyName.toArrayIndex(&isArrayIndex);

    if (isArrayIndex) {
        ArrayStorage* storage = m_storage;

        if (i < m_vectorLength) {
            ArrayEntity* ent = &storage->m_vector[i];
            if (ent->value) {
                JSValue*& valueSlot = ent->value;
                bool hadValue = valueSlot;
                valueSlot = 0;
                storage->m_numValuesInVector -= hadValue;
                ent->value = 0;
                return;
            }
        }

        if (SparseArrayValueMap* map = storage->m_sparseValueMap) {
            SparseArrayValueMap::iterator it = map->find(i);
            if (it != map->end()) {
                map->remove(it->first);
                return;
            }
        }
    }

    JSObject::removeDirect(Identifier::from(i));
}
