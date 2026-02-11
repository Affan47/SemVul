multimaster_ruv_search(Slapi_PBlock *pb)
{
        Slapi_Entry *e, *e_alt;
        Slapi_DN *suffix_sdn;
        Slapi_Operation *operation;

        slapi_pblock_get(pb, SLAPI_SEARCH_ENTRY_ORIG, &e);
        slapi_pblock_get( pb, SLAPI_OPERATION, &operation);

        if ((e == NULL) || (operation == NULL))
                return SLAPI_PLUGIN_SUCCESS;

        if (!operation_is_flag_set(operation, OP_FLAG_INTERNAL) && is_ruv_tombstone_entry(e)) {


                suffix_sdn = slapi_sdn_new();
                slapi_sdn_get_parent(slapi_entry_get_sdn(e), suffix_sdn);


                if ((e_alt = get_in_memory_ruv(suffix_sdn)) != NULL) {
                        slapi_pblock_set(pb, SLAPI_SEARCH_ENTRY_COPY, e_alt);
                }

                slapi_sdn_free(&suffix_sdn);
        }

        return SLAPI_PLUGIN_SUCCESS;
}
