kcm_ccache_remove_creds_internal(krb5_context context,
				 kcm_ccache ccache)
{
    struct kcm_creds *k;

    k = ccache->creds;
    while (k != NULL) {
	struct kcm_creds *old;

	krb5_free_cred_contents(context, &k->cred);
	old = k;
	k = k->next;
	free(old);
    }
    ccache->creds = NULL;

    return 0;
}
