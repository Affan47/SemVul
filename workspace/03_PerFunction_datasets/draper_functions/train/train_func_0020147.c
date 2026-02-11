kcm_ccache_get_uuids(krb5_context context, kcm_client *client, kcm_operation opcode, krb5_storage *sp)
{
    krb5_error_code ret;
    kcm_ccache p;

    ret = KRB5_FCC_NOFILE;

    HEIMDAL_MUTEX_lock(&ccache_mutex);

    for (p = ccache_head; p != NULL; p = p->next) {
	if ((p->flags & KCM_FLAGS_VALID) == 0)
	    continue;
	ret = kcm_access(context, client, opcode, p);
	if (ret) {
	    ret = 0;
	    continue;
	}
	krb5_storage_write(sp, p->uuid, sizeof(p->uuid));
    }

    HEIMDAL_MUTEX_unlock(&ccache_mutex);

    return ret;
}
