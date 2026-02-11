cli_print_volume_status_itables (dict_t *dict, char *prefix)
{
        int             ret = -1;
        char            key[1024] = {0,};
        uint32_t        active_size = 0;
        uint32_t        lru_size = 0;
        uint32_t        purge_size = 0;
        int             i =0;

        GF_ASSERT (dict);
        GF_ASSERT (prefix);

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.active_size", prefix);
        ret = dict_get_uint32 (dict, key, &active_size);
        if (ret)
                goto out;
        if (active_size != 0) {
                cli_out ("Active inodes:");
                cli_out ("%-40s %14s %14s %9s", "GFID", "Lookups", "Ref",
                         "IA type");
                cli_out ("%-40s %14s %14s %9s", "----", "-------", "---",
                         "-------");
        }
        for (i = 0; i < active_size; i++) {
                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "%s.active%d", prefix, i);
                cli_print_volume_status_inode_entry (dict, key);
        }
        cli_out (" ");

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.lru_size", prefix);
        ret = dict_get_uint32 (dict, key, &lru_size);
        if (ret)
                goto out;
        if (lru_size != 0) {
                cli_out ("LRU inodes:");
                cli_out ("%-40s %14s %14s %9s", "GFID", "Lookups", "Ref",
                         "IA type");
                cli_out ("%-40s %14s %14s %9s", "----", "-------", "---",
                         "-------");
        }
        for (i = 0; i < lru_size; i++) {
                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "%s.lru%d", prefix, i);
                cli_print_volume_status_inode_entry (dict, key);
        }
        cli_out (" ");

        memset (key, 0, sizeof (key));
        snprintf (key, sizeof (key), "%s.purge_size", prefix);
        ret = dict_get_uint32 (dict, key, &purge_size);
        if (ret)
                goto out;
        if (purge_size != 0) {
                cli_out ("Purged inodes:");
                cli_out ("%-40s %14s %14s %9s", "GFID", "Lookups", "Ref",
                         "IA type");
                cli_out ("%-40s %14s %14s %9s", "----", "-------", "---",
                         "-------");
        }
        for (i = 0; i < purge_size; i++) {
                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "%s.purge%d", prefix, i);
                cli_print_volume_status_inode_entry (dict, key);
        }

out:
        return;
}
