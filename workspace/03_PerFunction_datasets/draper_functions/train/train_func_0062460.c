sat_cfg_get_str_def (sat_cfg_str_e param)
{
    gchar *value;

    if (param < SAT_CFG_STR_NUM) {
        value = g_strdup (sat_cfg_str[param].defval);
    }
    else {
        sat_log_log (SAT_LOG_LEVEL_BUG,
                     _("%s: Unknown STR param index (%d)\n"),
                     __FUNCTION__, param);

        value = g_strdup ("ERROR");
    }

    return value;
}
