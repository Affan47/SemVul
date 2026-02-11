getp_remove_entry(VMG_ vm_obj_id_t self,
                                         vm_val_t *retval, uint *argc)
{
    vm_lookup_val *entry;
    vm_val_t key;
    uint hashval;
    vm_lookup_val *prv_entry;
    static CVmNativeCodeDesc desc(1);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    G_stk->pop(&key);


    entry = find_entry(vmg_ &key, &hashval, &prv_entry);


    if (entry != 0)
    {

        *retval = entry->val;


        add_undo_rec(vmg_ self, LOOKUPTAB_UNDO_DEL, &key, retval);


        unlink_entry(vmg_ entry, hashval, prv_entry);
    }
    else
    {

        retval->set_nil();
    }


    return TRUE;
}
