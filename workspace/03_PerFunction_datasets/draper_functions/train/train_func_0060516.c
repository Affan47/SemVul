load_extents(fr_vector<ft_uoff> & loop_file_extents,
					    fr_vector<ft_uoff> & free_space_extents, ft_uoff & ret_block_size_bitmask)
{
    ft_string path;
    const ft_string & job_dir = this_job.job_dir();
    ft_uoff block_size_bitmask = 0;
    FILE * f = NULL;
    const char * path_cstr = NULL;
    int err = 0;

    for (ft_size i = 0; err == 0 && i < FC_IO_EXTENTS_FILE_COUNT; i++) {
        path = job_dir;
        path += extents_filename[i];
        path_cstr = path.c_str();
        if ((f = fopen(path_cstr, "r")) == NULL) {
            err = ff_log(FC_ERROR, errno, "error opening persistence file '%s'", path_cstr);
            break;
        }
        if ((err = ff_load_extents_file(f, (i == 0 ? loop_file_extents : free_space_extents), block_size_bitmask)) != 0)
            err = ff_log(FC_ERROR, err, "error reading persistence file '%s'", path_cstr);

        if (fclose(f) != 0) {
            ff_log(FC_WARN, errno, "warning: failed to close persistence file '%s'", path_cstr);
            f = NULL;
        }
    }
    if (err == 0)
    	ret_block_size_bitmask = block_size_bitmask;

    return err;
}
