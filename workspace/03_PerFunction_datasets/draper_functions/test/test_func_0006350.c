pkinit_client(hx509_context contextp, hx509_ca_tbs tbs, struct cert_type_opt *opt)
{
    int ret;

    opt->pkinit++;

    ret = hx509_ca_tbs_add_eku(contextp, tbs, &asn1_oid_id_pkekuoid);
    if (ret)
	return ret;

    ret = hx509_ca_tbs_add_eku(context, tbs, &asn1_oid_id_ms_client_authentication);
    if (ret)
	return ret;

    return hx509_ca_tbs_add_eku(context, tbs, &asn1_oid_id_pkinit_ms_eku);
}
