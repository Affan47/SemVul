m4a_can_convert() {
    gchar *cmd = m4a_get_conversion_cmd();


    return cmd && cmd[0] && (prefs_get_int("conversion_target_format") != TARGET_FORMAT_AAC)
            && prefs_get_int("convert_m4a");
}
