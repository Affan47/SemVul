quit()
{
    if (this_log_appender != NULL) {
        ft_log::get_root_logger().remove_appender(* this_log_appender);
        this_log_appender = NULL;
    }
    if (this_log_file != NULL) {
        fclose(this_log_file);
        this_log_file = NULL;
    }
    this_dir.clear();
    for (ft_size i = 0; i < FC_STORAGE_SIZE_N; i++)
        this_storage_size[i] = 0;
    this_id = FC_JOB_ID_AUTODETECT;
}
