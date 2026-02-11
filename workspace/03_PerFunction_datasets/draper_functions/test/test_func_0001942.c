foreach(krb5_context context, HDB *db, hdb_entry_ex *ent, void *data)
{
    struct foreach_data *d = data;
    char *princ;
    krb5_error_code ret;
    ret = krb5_unparse_name(context, ent->entry.principal, &princ);
    if(ret)
	return ret;
    if(d->exp){
	if(fnmatch(d->exp, princ, 0) == 0 || fnmatch(d->exp2, princ, 0) == 0)
	    ret = add_princ(d, princ);
	else
	    free(princ);
    }else{
	ret = add_princ(d, princ);
    }
    if(ret)
	free(princ);
    return ret;
}
