__inode_path (inode_t *inode, const char *name, char **bufp)
{
        inode_table_t *table = NULL;
        dentry_t      *trav  = NULL;
        size_t         i     = 0, size = 0;
        int64_t        ret   = 0;
        int            len   = 0;
        char          *buf   = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return -1;
        }

        table = inode->table;

        for (trav = __dentry_search_arbit (inode); trav;
             trav = __dentry_search_arbit (trav->parent)) {
                i ++;
                i += strlen (trav->name);
                if (i > PATH_MAX) {
                        gf_log (table->name, GF_LOG_CRITICAL,
                                "possible infinite loop detected, "
                                "forcing break. name=(%s)", name);
                        ret = -ENOENT;
                        goto out;
                }
        }

        if (!__is_root_gfid (inode->gfid) &&
            (i == 0)) {
                gf_log (table->name, GF_LOG_WARNING,
                        "no dentry for non-root inode : %s",
                        uuid_utoa (inode->gfid));
                ret = -ENOENT;
                goto out;
        }

        if (name) {
                i++;
                i += strlen (name);
        }

        ret = i;
        size = i + 1;
        buf = GF_CALLOC (size, sizeof (char), gf_common_mt_char);
        if (buf) {

                buf[size - 1] = 0;

                if (name) {
                        len = strlen (name);
                        strncpy (buf + (i - len), name, len);
                        buf[i-len-1] = '/';
                        i -= (len + 1);
                }

                for (trav = __dentry_search_arbit (inode); trav;
                     trav = __dentry_search_arbit (trav->parent)) {
                        len = strlen (trav->name);
                        strncpy (buf + (i - len), trav->name, len);
                        buf[i-len-1] = '/';
                        i -= (len + 1);
                }
                *bufp = buf;
        } else {
                ret = -ENOMEM;
        }

out:
        if (__is_root_gfid (inode->gfid) && !name) {
                ret = 1;
                if (buf) {
                        GF_FREE (buf);
                }
                buf = GF_CALLOC (ret + 1, sizeof (char), gf_common_mt_char);
                if (buf) {
                        strcpy (buf, "/");
                        *bufp = buf;
                } else {
                        ret = -ENOMEM;
                }
        }

        return ret;
}
