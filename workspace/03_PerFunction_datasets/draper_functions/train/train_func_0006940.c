sp_priv_dump (xlator_t *this)
{
        sp_private_t            *priv         = NULL;
        uint32_t                total_entries = 0;
        uint32_t                ret           = -1;
        char                    key[GF_DUMP_MAX_BUF_LEN];
        char                    key_prefix[GF_DUMP_MAX_BUF_LEN];

        GF_VALIDATE_OR_GOTO ("stat-prefetch", this, out);
        GF_VALIDATE_OR_GOTO (this->name, this->private, out);

        priv = this->private;

        total_entries = priv->entries;

        gf_proc_dump_build_key (key_prefix, "xlator.performance.stat-prefetch",
                                "priv");
        gf_proc_dump_add_section (key_prefix);

        gf_proc_dump_build_key (key, key_prefix, "max_allowed_entries");
        gf_proc_dump_write (key, "%lu", GF_SP_CACHE_ENTRIES_EXPECTED);
        gf_proc_dump_build_key (key, key_prefix, "num_entries_cached");
        gf_proc_dump_write (key, "%lu",(unsigned long)total_entries);
        ret = 0;

out:
        return ret;
}
