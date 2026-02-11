dfs_load_table(cpl_frameset *frameset, const char *category, int ext)
{
    const char *func = "dfs_load_table";

    cpl_frame  *frame = NULL;
    cpl_table  *table = NULL;


    frame = cpl_frameset_find(frameset, category);

    if (frame) {
        table = cpl_table_load(cpl_frame_get_filename(frame), ext, 1);
        if (table == NULL) {
            cpl_msg_error(cpl_error_get_where(), "%s", cpl_error_get_message());
            cpl_msg_error(func, "Cannot load table %s",
                          cpl_frame_get_filename(frame));
        }
        else
            cpl_frame_set_group(frame, CPL_FRAME_GROUP_CALIB);
    }

    return table;
}
