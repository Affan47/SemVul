wti_mpc_status(StonithPlugin * s)
{
    struct pluginDevice *ad;
    char *ident;

    DEBUGCALL;

    ERRIFNOTCONFIGED(s, S_OOPS);

    ad = (struct pluginDevice *) s;

    if ((ident = MPC_read(ad->sptr, OID_IDENT, ASN_OCTET_STR)) == NULL) {
	LOG(PIL_CRIT, "%s: cannot read ident.", __FUNCTION__);
	return (S_ACCESS);
    }


    return (S_OK);
}
