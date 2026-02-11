aisc_link(dllpublic_ext * parent, dllheader_ext * mh) {
    if (!mh) {
        CORE;
        return "Object is (NULL)";
    }
    if (mh->parent) {
        CORE;
        return "Object already linked";
    }
    if (!parent) {
        CORE;
        return "Parent is (NULL)";
    }
    if (parent->key != mh->key) {
        CORE;
        return "Parent key doesnt match Object key";
    }
    if (mh->ident) {
        if (strlen(mh->ident) <= 0) {
            CORE;
            return "Too short ident";
        }
        if (parent->hash) {
            if (aisc_read_hash((struct aisc_hash_node **)parent->hash, mh->ident)) {
                CORE;
                return "Object already in list";
            } else {
                aisc_insert_hash((struct aisc_hash_node **)parent->hash, mh->ident, (long)mh);
            }
        } else {
            parent->hash = (long)aisc_init_hash(HASH_SIZE);
            aisc_insert_hash((struct aisc_hash_node **)parent->hash, mh->ident, (long)mh);
        }
    }
    mh->next = mh->previous = NULL;
    if (!parent->first) {
        parent->cnt = 1;
        parent->first = mh;
        parent->last = mh;
    } else {
        parent->cnt++;
        mh->previous = parent->last;
        parent->last->next = mh;
        parent->last = mh;
    }
    mh->parent = parent;
    return 0;
}
