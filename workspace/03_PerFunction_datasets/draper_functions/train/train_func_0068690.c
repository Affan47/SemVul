orte_sstore_base_get_all_snapshots(opal_list_t *all_snapshots, char *basedir)
{
#ifndef HAVE_DIRENT_H
    return ORTE_ERR_NOT_SUPPORTED;
#else
    int ret, exit_status = ORTE_SUCCESS;
    char *loc_basedir = NULL;
    char * tmp_str = NULL, * metadata_file = NULL;
    DIR *dirp = NULL;
    struct dirent *dir_entp = NULL;
    struct stat file_status;
    orte_sstore_base_global_snapshot_info_t *global_snapshot = NULL;


    if( NULL == all_snapshots ||
        (NULL == orte_sstore_base_global_snapshot_dir && NULL == basedir)) {
        ORTE_ERROR_LOG(ORTE_ERROR);
        exit_status = ORTE_ERROR;
        goto cleanup;
    }

    if( NULL == basedir ) {
        loc_basedir = strdup(orte_sstore_base_global_snapshot_dir);
    } else {
        loc_basedir = strdup(basedir);
    }


    dirp = opendir(loc_basedir);
    while( NULL != (dir_entp = readdir(dirp))) {

        if( 0 == strncmp("..", dir_entp->d_name, strlen("..") ) ||
            0 == strncmp(".",  dir_entp->d_name, strlen(".")  ) ) {
            continue;
        }


        asprintf(&tmp_str, "%s/%s", loc_basedir, dir_entp->d_name);
        if(0 != (ret = stat(tmp_str, &file_status) ) ){
            free( tmp_str);
            tmp_str = NULL;
            continue;
        } else {

            if(S_ISDIR(file_status.st_mode) ) {
                asprintf(&metadata_file, "%s/%s",
                         tmp_str,
                         orte_sstore_base_global_metadata_filename);
                if(0 != (ret = stat(metadata_file, &file_status) ) ){
                    free( tmp_str);
                    tmp_str = NULL;
                    free( metadata_file);
                    metadata_file = NULL;
                    continue;
                } else {
                    if(S_ISREG(file_status.st_mode) ) {
                        global_snapshot = OBJ_NEW(orte_sstore_base_global_snapshot_info_t);

                        global_snapshot->ss_handle = 1;
                        global_snapshot->basedir = strdup(loc_basedir);
                        asprintf(&(global_snapshot->reference),
                                 "%s",
                                 dir_entp->d_name);
                        asprintf(&(global_snapshot->metadata_filename),
                                 "%s/%s/%s",
                                 global_snapshot->basedir,
                                 global_snapshot->reference,
                                 orte_sstore_base_global_metadata_filename);

                        opal_list_append(all_snapshots, &(global_snapshot->super));
                    }
                }
                free( metadata_file);
                metadata_file = NULL;
            }
        }

        free( tmp_str);
        tmp_str = NULL;
    }

    closedir(dirp);

 cleanup:
    if( NULL != loc_basedir ) {
        free(loc_basedir);
        loc_basedir = NULL;
    }

    if( NULL != tmp_str) {
        free( tmp_str);
        tmp_str = NULL;
    }

    return exit_status;
#endif
}
