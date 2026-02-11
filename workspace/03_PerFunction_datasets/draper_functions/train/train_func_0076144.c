vattr_helper_get_entry_conts_no_subtypes(Slapi_Entry *e,const char *type, vattr_get_thang **my_get)
{
        int                     attr_count = 0;
        Slapi_Attr *a = attrlist_find(e->e_attrs,type);

        if (a) {
                attr_count = 1;
                *my_get = (vattr_get_thang *)slapi_ch_calloc(1, sizeof(vattr_get_thang));
                (*my_get)[0].get_present = 1;
                (*my_get)[0].get_name_disposition = SLAPI_VIRTUALATTRS_TYPE_NAME_MATCHED_EXACTLY_OR_ALIAS;
                (*my_get)[0].get_type_name = a->a_type;
                (*my_get)[0].get_present_values = &(a->a_present_values);
                (*my_get)[0].get_attr = a;
        }

        return attr_count;
}
