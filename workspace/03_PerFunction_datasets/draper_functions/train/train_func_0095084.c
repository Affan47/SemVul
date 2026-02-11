oc_replace_nolock(const char *ocname, struct objclass *newoc) {
    struct objclass	*oc, *pnext;
    int				rc = LDAP_SUCCESS;
    PRBool saw_sup=PR_FALSE;

    oc  = g_get_global_oc_nolock();

    if(newoc->oc_superior == NULL)
    {
        saw_sup=PR_TRUE;
    }

    if (strcasecmp (oc->oc_name, ocname) == 0) {
        newoc->oc_next=oc->oc_next;
        g_set_global_oc_nolock ( newoc );
        oc_free( &oc );
    } else {
        for (pnext = oc ; pnext  != NULL;
        oc = pnext, pnext = pnext->oc_next) {
            if(pnext->oc_name == NULL) {
                rc = LDAP_OPERATIONS_ERROR;
                break;
            }
            if(newoc->oc_superior != NULL) {
                if(strcasecmp( pnext->oc_name, newoc->oc_superior) == 0)
                {
                    saw_sup=PR_TRUE;
                }
            }
            if (strcasecmp ( pnext->oc_name, ocname ) == 0) {
                if(saw_sup)
                {
                    oc->oc_next=newoc;
                    newoc->oc_next=pnext->oc_next;
                    oc_free( &pnext );
                    break;

                } else
                {
                    rc = LDAP_TYPE_OR_VALUE_EXISTS;
                    break;
                }

            }
        }
    }
    return rc;
}
