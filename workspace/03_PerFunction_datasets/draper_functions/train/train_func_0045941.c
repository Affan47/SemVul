_gd_get_option_type (char *key)
{
        struct volopt_map_entry *vmep = NULL;
        void                    *dl_handle = NULL;
        volume_opt_list_t       vol_opt_list = {{0},};
        int                     ret = -1;
        volume_option_t         *opt = NULL;
        char                    *xlopt_key = NULL;
        volume_option_type_t    opt_type = GF_OPTION_TYPE_MAX;

        GF_ASSERT (key);

        vmep = _gd_get_vmep (key);

        if (vmep) {
                INIT_LIST_HEAD (&vol_opt_list.list);
                ret = xlator_volopt_dynload (vmep->voltype, &dl_handle,
                                             &vol_opt_list);
                if (ret)
                        goto out;

                if (_get_xlator_opt_key_from_vme (vmep, &xlopt_key))
                        goto out;

                opt = xlator_volume_option_get_list (&vol_opt_list, xlopt_key);
                _free_xlator_opt_key (xlopt_key);

                if (opt)
                        opt_type = opt->type;
        }

out:
        if (dl_handle) {
                dlclose (dl_handle);
                dl_handle = NULL;
        }

        return opt_type;
}
