hash_lookup(scm_hash_table *tab, ScmObj key, scm_intobj_t datum, int flag)
{
    size_t i;
    hashval_t hashval;
    scm_hash_entry *ent;


    hashval = (hashval_t)key;
    if (sizeof(hashval) > 4) {
        hashval /= sizeof(ScmCell);
        hashval &= 0xffffffff;
    }

    hashval *= 2654435761UL;


    for (i = 0; i < tab->size; i++) {
        ent = &(tab->ents)[(hashval + i) & (tab->size - 1)];
        if (!OCCUPIED(ent)) {
            if (flag & HASH_INSERT) {
                ent->key = key;
                ent->datum = datum;
                tab->used++;


                if (tab->used * 3 > tab->size * 2)
                    hash_grow(tab);
            }
            return NULL;
        }
        if (EQ(ent->key, key))
            return ent;
    }


    SCM_NOTREACHED;
}
