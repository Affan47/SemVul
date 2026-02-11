vlv_SearchIndexEntry(Slapi_PBlock *pb, Slapi_Entry* entryBefore, Slapi_Entry* entryAfter, int *returncode, char *returntext, void *arg)
{
    char *name= slapi_entry_attr_get_charptr(entryBefore,type_vlvName);
	backend *be= ((ldbm_instance*)arg)->inst_be;
    if (name!=NULL)
    {
        struct vlvIndex* p= vlv_find_searchname(name, be);
        slapi_ch_free((void **) &name);
        if(p!=NULL)
        {
            if(vlvIndex_enabled(p))
            {
                slapi_entry_attr_set_charptr(entryBefore, type_vlvEnabled, "1");
            }
            else
            {
                slapi_entry_attr_set_charptr(entryBefore, type_vlvEnabled, "0");
            }
            slapi_entry_attr_set_ulong(entryBefore, type_vlvUses, p->vlv_uses);
        }
    }
    return SLAPI_DSE_CALLBACK_OK;
}
