performmode_relative_id(const char *id, GEN_PERFORM_MODE pmode) {
    return GBS_global_string("%s_%s", GEN_PERFORM_MODE_id[pmode], id);
}
