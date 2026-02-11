dht_priv_dump (xlator_t *this)
{
        char            key_prefix[GF_DUMP_MAX_BUF_LEN];
        char            key[GF_DUMP_MAX_BUF_LEN];
        int             i = 0;
        dht_conf_t      *conf = NULL;
        int             ret = -1;

        GF_VALIDATE_OR_GOTO ("dht", this, out);

        conf = this->private;

        if (!conf)
                return -1;

        ret = TRY_LOCK(&conf->subvolume_lock);

        if (ret != 0) {
                gf_log("", GF_LOG_WARNING, "Unable to lock dht subvolume %s",
                       this->name);
                return ret;
        }

        gf_proc_dump_add_section("xlator.cluster.dht.%s.priv", this->name);
        gf_proc_dump_build_key(key_prefix,"xlator.cluster.dht","%s.priv",
                               this->name);
        gf_proc_dump_write("subvol_cnt","%d", conf->subvolume_cnt);
        for (i = 0; i < conf->subvolume_cnt; i++) {
                sprintf (key, "subvolumes[%d]", i);
                gf_proc_dump_write(key, "%s.%s", conf->subvolumes[i]->type,
                                   conf->subvolumes[i]->name);
                if (conf->file_layouts && conf->file_layouts[i]){
                        sprintf (key, "file_layouts[%d]", i);
                        dht_layout_dump(conf->file_layouts[i], key);
                }
                if (conf->dir_layouts && conf->dir_layouts[i]) {
                        sprintf (key, "dir_layouts[%d]", i);
                        dht_layout_dump(conf->dir_layouts[i], key);
                }
                if (conf->subvolume_status) {

                        sprintf (key, "subvolume_status[%d]", i);
                        gf_proc_dump_write(key, "%d",
                                           (int)conf->subvolume_status[i]);
                }

        }

        gf_proc_dump_write("search_unhashed", "%d", conf->search_unhashed);
        gf_proc_dump_write("gen", "%d", conf->gen);
        gf_proc_dump_write("min_free_disk", "%lu", conf->min_free_disk);
	gf_proc_dump_write("min_free_inodes", "%lu", conf->min_free_inodes);
        gf_proc_dump_write("disk_unit", "%c", conf->disk_unit);
        gf_proc_dump_write("refresh_interval", "%d", conf->refresh_interval);
        gf_proc_dump_write("unhashed_sticky_bit", "%d", conf->unhashed_sticky_bit);
        if (conf ->du_stats) {
                gf_proc_dump_write("du_stats.avail_percent", "%lf",
                                   conf->du_stats->avail_percent);
                gf_proc_dump_write("du_stats.avail_space", "%lu",
                                   conf->du_stats->avail_space);
		gf_proc_dump_write("du_stats.avail_inodes", "%lf",
                                   conf->du_stats->avail_inodes);
                gf_proc_dump_write("du_stats.log", "%lu", conf->du_stats->log);
        }
        gf_proc_dump_write("last_stat_fetch", "%s", ctime(&conf->last_stat_fetch.tv_sec));

        UNLOCK(&conf->subvolume_lock);

out:
        return ret;
}
