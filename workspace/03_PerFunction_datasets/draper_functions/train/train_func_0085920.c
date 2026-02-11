cb_create_loop_control (
     const ber_int_t hops,
     LDAPControl **ctrlp)

{
    BerElement      *ber;
    int             rc;

    if ((ber = ber_alloc()) == NULL)
        return -1;

    if ( ber_printf( ber, "i", hops ) < 0) {
        ber_free(ber,1);
        return -1;
    }

    rc = slapi_build_control( CB_LDAP_CONTROL_CHAIN_SERVER, ber, 0, ctrlp);

    ber_free(ber,1);

    return rc;
}
