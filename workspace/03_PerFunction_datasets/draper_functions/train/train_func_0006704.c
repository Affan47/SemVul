sat_pref_single_sat_ok     (GKeyFile *cfg)
{

    if (dirty) {

        if (cfg != NULL) {
            g_key_file_set_integer (cfg,
                        MOD_CFG_SINGLE_SAT_SECTION,
                        MOD_CFG_SINGLE_SAT_FIELDS,
                        flags);

        }
        else {
            sat_cfg_set_int (SAT_CFG_INT_SINGLE_SAT_FIELDS, flags);
        }
    }
    else if (reset) {

        if (cfg != NULL) {

            g_key_file_remove_key (cfg,
                           MOD_CFG_SINGLE_SAT_SECTION,
                           MOD_CFG_SINGLE_SAT_FIELDS,
                           NULL);

        }
        else {

            sat_cfg_reset_int (SAT_CFG_INT_SINGLE_SAT_FIELDS);
        }
    }

    dirty = FALSE;
    reset = FALSE;
}
