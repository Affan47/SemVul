hdb_add_master_key(krb5_context context, krb5_keyblock *key,
		   hdb_master_key *inout)
{
    int vno = 0;
    hdb_master_key p;
    krb5_error_code ret;

    for(p = *inout; p; p = p->next)
	vno = max(vno, p->keytab.vno);
    vno++;
    ret = hdb_process_master_key(context, vno, key, 0, &p);
    if(ret)
	return ret;
    p->next = *inout;
    *inout = p;
    return 0;
}
