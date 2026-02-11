ompi_show_all_mca_params(int32_t rank, int requested, char *nodename) {
    const mca_base_var_t *var;
    int var_count, i, ret;
    FILE *fp = NULL;
    time_t timestamp;
    char **var_dump;

    if (rank != 0) {
        return OMPI_SUCCESS;
    }

    timestamp = time(NULL);


    if (0 != strlen(ompi_mpi_show_mca_params_file)) {
        if ( NULL == (fp = fopen(ompi_mpi_show_mca_params_file, "w")) ) {
            opal_output(0, "Unable to open file <%s> to write MCA parameters", ompi_mpi_show_mca_params_file);
            return OMPI_ERR_FILE_OPEN_FAILURE;
        }
        fprintf(fp, "#\n");
        fprintf(fp, "# This file was automatically generated on %s", ctime(&timestamp));
        fprintf(fp, "# by MPI_COMM_WORLD rank %d (out of a total of %d) on %s\n", rank, requested, nodename );
        fprintf(fp, "#\n");
    }

    var_count = mca_base_var_get_count ();
    for (i = 0 ; i < var_count ; ++i) {
        ret = mca_base_var_get (i, &var);
        if (OPAL_SUCCESS != ret) {
            continue;
        }


        if (MCA_BASE_VAR_FLAG_INTERNAL & var->mbv_flags) {
            continue;
        }


        if (MCA_BASE_VAR_SOURCE_DEFAULT == var->mbv_source && !show_default_mca_params) {
            continue;
        }


        if ((MCA_BASE_VAR_SOURCE_FILE == var->mbv_source ||
             MCA_BASE_VAR_SOURCE_OVERRIDE) && !show_file_mca_params) {
            continue;
        }


        if (MCA_BASE_VAR_SOURCE_ENV == var->mbv_source && !show_enviro_mca_params) {
            continue;
        }


        if (MCA_BASE_VAR_SOURCE_OVERRIDE == var->mbv_source && !show_override_mca_params) {
            continue;
        }

        ret = mca_base_var_dump (i, &var_dump, MCA_BASE_VAR_DUMP_SIMPLE);
        if (OPAL_SUCCESS != ret) {
            continue;
        }


        if (0 != strlen(ompi_mpi_show_mca_params_file)) {
            fprintf(fp, "%s\n", var_dump[0]);
        } else {
            opal_output(0, "%s\n", var_dump[0]);
        }
        free (var_dump[0]);
        free (var_dump);
    }


    if (0 != strlen(ompi_mpi_show_mca_params_file)) {
        fclose(fp);
    }

    return OMPI_SUCCESS;
}
