remembered_name (const char *name, struct list_head *entries)
{
        struct entry_name *e   = NULL;
        gf_boolean_t       ret = _gf_false;

        list_for_each_entry (e, entries, list) {
                if (!strcmp (name, e->name)) {
                        ret = _gf_true;
                        goto out;
                }
        }

out:
        return ret;
}
