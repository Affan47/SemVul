krb5_rc_get_lifespan(krb5_context context,
		     krb5_rcache id,
		     krb5_deltat *auth_lifespan)
{
    FILE *f = fopen(id->name, "r");
    int r;
    struct rc_entry ent;
    r = fread(&ent, sizeof(ent), 1, f);
    fclose(f);
    if(r){
	*auth_lifespan = ent.stamp;
	return 0;
    }
    krb5_clear_error_message (context);
    return KRB5_RC_IO_UNKNOWN;
}
