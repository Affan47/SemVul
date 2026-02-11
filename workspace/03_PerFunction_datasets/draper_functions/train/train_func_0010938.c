_free_xlator_opt_key (char *key)
{
        GF_ASSERT (key);

        if (!strcmp (key, AUTH_ALLOW_OPT_KEY) ||
            !strcmp (key, AUTH_REJECT_OPT_KEY) ||
            !strcmp (key, NFS_DISABLE_OPT_KEY))
                GF_FREE (key);

        return;
}
