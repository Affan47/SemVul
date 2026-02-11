init (xlator_t *this)
{
        struct posix_acl_conf   *conf = NULL;
        struct posix_acl        *minacl = NULL;
        struct posix_ace        *minace = NULL;

        conf = CALLOC (1, sizeof (*conf));
        if (!conf) {
                gf_log (this->name, GF_LOG_ERROR,
                        "out of memory");
                return -1;
        }

        LOCK_INIT (&conf->acl_lock);

        this->private = conf;

        minacl = posix_acl_new (this, 3);
        if (!minacl)
                return -1;

        minace = minacl->entries;
        minace[0].tag = POSIX_ACL_USER_OBJ;
        minace[1].tag = POSIX_ACL_GROUP_OBJ;
        minace[2].tag = POSIX_ACL_OTHER;

        conf->minimal_acl = minacl;

        GF_OPTION_INIT ("super-uid", conf->super_uid, uint32, err);

        return 0;
err:
        return -1;
}
