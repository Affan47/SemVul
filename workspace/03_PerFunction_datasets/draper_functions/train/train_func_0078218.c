vlv_parse_request_control( backend *be, struct berval *vlv_spec_ber,struct vlv_request* vlvp)
{


    BerElement *ber = NULL;
    int return_value = LDAP_SUCCESS;

    vlvp->value.bv_len = 0;
    vlvp->value.bv_val = NULL;

    if (!BV_HAS_DATA(vlv_spec_ber))
    {
        return_value= LDAP_OPERATIONS_ERROR;
        return return_value;
    }

    ber = ber_init(vlv_spec_ber);
    if (ber_scanf(ber, "{ii", &vlvp->beforeCount, &vlvp->afterCount) == LBER_ERROR)
    {
        return_value= LDAP_OPERATIONS_ERROR;
    }
    else
    {
        LDAPDebug( LDAP_DEBUG_TRACE, "vlv_parse_request_control: Before=%d After=%d\n",
                   vlvp->beforeCount, vlvp->afterCount, 0 );
        if (ber_scanf(ber,"t",&vlvp->tag) == LBER_ERROR)
        {
            return_value= LDAP_OPERATIONS_ERROR;
        }
        else
        {
            switch(vlvp->tag)
            {
            case LDAP_TAG_VLV_BY_INDEX:

                vlvp->tag= 0;
                if (ber_scanf(ber, "{ii}}", &vlvp->index, &vlvp->contentCount) == LBER_ERROR)
                {
                    if (ISLEGACY(be)) {
                        return_value = LDAP_OPERATIONS_ERROR;
                    } else {
                        return_value = LDAP_VIRTUAL_LIST_VIEW_ERROR;
                    }
                }
                else
                {

                    if(vlvp->index!=0)
                    {
                        vlvp->index--;
                    }
                    LDAPDebug( LDAP_DEBUG_TRACE, "vlv_parse_request_control: Index=%d Content=%d\n", vlvp->index, vlvp->contentCount, 0 );
                }
                break;
            case LDAP_TAG_VLV_BY_VALUE:

                vlvp->tag= 1;
                if (ber_scanf(ber,"o}",&vlvp->value) == LBER_ERROR)
                {
                    if (ISLEGACY(be)) {
                        return_value = LDAP_OPERATIONS_ERROR;
                    } else {
                        return_value = LDAP_VIRTUAL_LIST_VIEW_ERROR;
                    }
                }
                {

                    char *p= slapi_ch_malloc(vlvp->value.bv_len+1);
                    strncpy(p,vlvp->value.bv_val,vlvp->value.bv_len);
                    p[vlvp->value.bv_len]= '\0';
                    LDAPDebug( LDAP_DEBUG_TRACE, "vlv_parse_request_control: Value=%s\n", p, 0, 0 );
                    slapi_ch_free( (void**)&p);
                }
                break;
            default:
                if (ISLEGACY(be)) {
                    return_value = LDAP_OPERATIONS_ERROR;
                } else {
                    return_value = LDAP_VIRTUAL_LIST_VIEW_ERROR;
                }
            }
        }
    }


   	ber_free(ber,1);

	return return_value;
}
