server_inode (xlator_t *this)
{
        server_conf_t        *conf = NULL;
        server_connection_t  *trav = NULL;
        char                 key[GF_DUMP_MAX_BUF_LEN];
        int                  i = 1;
        int                  ret = -1;

        GF_VALIDATE_OR_GOTO ("server", this, out);

        conf = this->private;
        if (!conf) {
                gf_log (this->name, GF_LOG_WARNING,
                        "conf null in xlator");
                return -1;
        }

        ret = pthread_mutex_trylock (&conf->mutex);
        if (ret)
                goto out;

        list_for_each_entry (trav, &conf->conns, list) {
                ret = pthread_mutex_trylock (&trav->lock);
                if (!ret)
                {
                        gf_proc_dump_build_key(key,
                                               "conn","%d.ltable", i);
                        gf_proc_dump_add_section(key);
                        ltable_dump (trav);
                        i++;
                        pthread_mutex_unlock (&trav->lock);
                }else
                        continue;
        }
        pthread_mutex_unlock (&conf->mutex);

        ret = 0;
out:
        if (ret)
                gf_proc_dump_write ("Unable to dump the lock table",
                                    "(Lock acquisition failed) %s",
                                    this?this->name:"server");

        return ret;
}
