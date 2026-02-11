hdb_free_entry(krb5_context context, hdb_entry_ex *ent)
{
    Key *k;
    size_t i;

    if (ent->free_entry)
	(*ent->free_entry)(context, ent);

    for(i = 0; i < ent->entry.keys.len; i++) {
	k = &ent->entry.keys.val[i];

	memset (k->key.keyvalue.data, 0, k->key.keyvalue.length);
    }
    free_hdb_entry(&ent->entry);
}
