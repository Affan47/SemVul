cli_local_wipe (cli_local_t *local)
{
        if (local) {
                GF_FREE (local->get_vol.volname);
                if (local->dict)
                        dict_unref (local->dict);
                GF_FREE (local);
        }

        return;
}
