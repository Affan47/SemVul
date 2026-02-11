can_skip_filter_test(
    Slapi_PBlock        *pb,
    struct slapi_filter    *f,
    int scope,
    IDList *idl
)
{
    int rc = 0;


    if ( ALLIDS(idl)) {

        return rc;
    }


    if ( scope == LDAP_SCOPE_BASE ) {


        return rc;
    }


    rc = grok_filter(f);


    if (rc != 0) {
        char *type = NULL;
        char *basetype = NULL;


        slapi_filter_get_attribute_type(f, &type);
        basetype = slapi_attr_basetype(type, NULL, 0);


        if (strcasecmp(type, basetype) != 0) {


            rc = 0;
        }
        slapi_ch_free_string(&basetype);
    }

    return rc;
}
