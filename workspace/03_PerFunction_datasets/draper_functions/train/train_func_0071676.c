rpcsvc_transport_check_volume_general (dict_t *options, rpc_transport_t *trans)
{
        int             addrchk = RPCSVC_AUTH_REJECT;
        int             namechk = RPCSVC_AUTH_REJECT;
        gf_boolean_t    namelookup = _gf_false;
        char            *namestr = NULL;
        int             ret = 0;

        if ((!options) || (!trans))
                return RPCSVC_AUTH_REJECT;


        if ((dict_get (options, "rpc-auth.addr.namelookup"))) {
                ret = dict_get_str (options, "rpc-auth.addr.namelookup"
                                    , &namestr);
                if (ret == 0)
                        ret = gf_string2boolean (namestr, &namelookup);
        }


        if (namelookup)
                namechk = rpcsvc_transport_peer_check_name (options, NULL, trans);
        addrchk = rpcsvc_transport_peer_check_addr (options, NULL, trans);

        if (namelookup)
                ret = rpcsvc_combine_gen_spec_addr_checks (addrchk, namechk);
        else
                ret = addrchk;

        return ret;
}
