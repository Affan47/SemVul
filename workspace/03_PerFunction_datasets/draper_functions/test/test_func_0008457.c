kcm_release_ccache(krb5_context context, kcm_ccache c)
{
    krb5_error_code ret = 0;

    KCM_ASSERT_VALID(c);

    HEIMDAL_MUTEX_lock(&c->mutex);
    if (c->refcnt == 1) {
	kcm_free_ccache_data_internal(context, c);
	free(c);
    } else {
	c->refcnt--;
	HEIMDAL_MUTEX_unlock(&c->mutex);
    }

    return ret;
}
