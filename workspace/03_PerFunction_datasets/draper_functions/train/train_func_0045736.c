fini (xlator_t *this)
{
        int                   i = 0;
        dht_conf_t           *conf = NULL;
        struct switch_struct *trav = NULL;
        struct switch_struct *prev = NULL;

        conf = this->private;

        if (conf) {
                trav = (struct switch_struct *)conf->private;
                conf->private = NULL;
                while (trav) {
                        GF_FREE (trav->array);
                        prev = trav;
                        trav = trav->next;
                        GF_FREE (prev);
                }

                if (conf->file_layouts) {
                        for (i = 0; i < conf->subvolume_cnt; i++) {
                                GF_FREE (conf->file_layouts[i]);
                        }
                        GF_FREE (conf->file_layouts);
                }

                GF_FREE (conf->subvolumes);

                GF_FREE (conf->subvolume_status);

                GF_FREE (conf);
        }

        return;
}
