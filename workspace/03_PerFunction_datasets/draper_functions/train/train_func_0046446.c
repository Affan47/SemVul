dht_layout_dump (dht_layout_t  *layout, const char *prefix)
{

        char    key[GF_DUMP_MAX_BUF_LEN];
        int     i = 0;

        if (!layout)
                goto out;
        if (!prefix)
                goto out;

        gf_proc_dump_build_key(key, prefix, "cnt");
        gf_proc_dump_write(key, "%d", layout->cnt);
        gf_proc_dump_build_key(key, prefix, "preset");
        gf_proc_dump_write(key, "%d", layout->preset);
        gf_proc_dump_build_key(key, prefix, "gen");
        gf_proc_dump_write(key, "%d", layout->gen);
        if (layout->type != IA_INVAL) {
                gf_proc_dump_build_key(key, prefix, "inode type");
                gf_proc_dump_write(key, "%d", layout->type);
        }

        if  (!IA_ISDIR (layout->type))
                goto out;

        for (i = 0; i < layout->cnt; i++) {
                gf_proc_dump_build_key(key, prefix,"list[%d].err", i);
                gf_proc_dump_write(key, "%d", layout->list[i].err);
                gf_proc_dump_build_key(key, prefix,"list[%d].start", i);
                gf_proc_dump_write(key, "%u", layout->list[i].start);
                gf_proc_dump_build_key(key, prefix,"list[%d].stop", i);
                gf_proc_dump_write(key, "%u", layout->list[i].stop);
                if (layout->list[i].xlator) {
                        gf_proc_dump_build_key(key, prefix,
                                               "list[%d].xlator.type", i);
                        gf_proc_dump_write(key, "%s",
                                           layout->list[i].xlator->type);
                        gf_proc_dump_build_key(key, prefix,
                                               "list[%d].xlator.name", i);
                        gf_proc_dump_write(key, "%s",
                                           layout->list[i].xlator->name);
                }
        }

out:
        return;
}
