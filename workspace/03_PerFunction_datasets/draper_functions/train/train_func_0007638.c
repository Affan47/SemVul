_volfile_update_checksum (xlator_t *this, char *key, uint32_t checksum)
{
        server_conf_t       *conf         = NULL;
        struct _volfile_ctx *temp_volfile = NULL;

        conf         = this->private;
        temp_volfile = conf->volfile;

        while (temp_volfile) {
                if ((NULL == key) && (NULL == temp_volfile->key))
                        break;
                if ((NULL == key) || (NULL == temp_volfile->key)) {
                        temp_volfile = temp_volfile->next;
                        continue;
                }
                if (strcmp (temp_volfile->key, key) == 0)
                        break;
                temp_volfile = temp_volfile->next;
        }

        if (!temp_volfile) {
                temp_volfile = GF_CALLOC (1, sizeof (struct _volfile_ctx),
                                          gf_server_mt_volfile_ctx_t);
                if (!temp_volfile)
                        goto out;
                temp_volfile->next  = conf->volfile;
                temp_volfile->key   = (key)? gf_strdup (key): NULL;
                temp_volfile->checksum = checksum;

                conf->volfile = temp_volfile;
                goto out;
        }

        if (temp_volfile->checksum != checksum) {
                gf_log (this->name, GF_LOG_INFO,
                        "the volume file got modified between earlier access "
                        "and now, this may lead to inconsistency between "
                        "clients, advised to remount client");
                temp_volfile->checksum  = checksum;
        }

out:
        return 0;
}
