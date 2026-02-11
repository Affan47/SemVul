assimilate_handler(
    WORKUNIT& wu, vector<RESULT>& , RESULT& canonical_result
) {
    int retval;
    char buf[1024];
    unsigned int i;

    retval = boinc_mkdir(config.project_path("sample_results"));
    if (retval) return retval;

    if (wu.canonical_resultid) {
        vector<OUTPUT_FILE_INFO> output_files;
        const char *copy_path;
        get_output_file_infos(canonical_result, output_files);
        unsigned int n = output_files.size();
        bool file_copied = false;
        for (i=0; i<n; i++) {
            OUTPUT_FILE_INFO& fi = output_files[i];
            if (n==1) {
                copy_path = config.project_path("sample_results/%s", wu.name);
            } else {
                copy_path = config.project_path("sample_results/%s_%d", wu.name, i);
            }
            retval = boinc_copy(fi.path.c_str() , copy_path);
            if (!retval) {
                file_copied = true;
            }
        }
        if (!file_copied) {
            copy_path = config.project_path(
                "sample_results/%s_%s", wu.name, "no_output_files"
            );
            FILE* f = fopen(copy_path, "w");
            fclose(f);
        }
    } else {
        sprintf(buf, "%s: 0x%x\n", wu.name, wu.error_mask);
        return write_error(buf);
    }
    return 0;
}
