cpl_dfs_save_paf(const char * instrume, const char *recipe,
                               const cpl_propertylist * paflist,
                               const char * filename)
{

    FILE * paf;
    cpl_error_code status;


    cpl_ensure_code(instrume  != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(recipe    != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(paflist   != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(filename  != NULL, CPL_ERROR_NULL_INPUT);


    paf = cpl_dfs_paf_init(instrume, recipe, filename);

    cpl_ensure_code(paf != NULL, cpl_error_get_code());

    status = cpl_dfs_paf_dump(paflist, paf);
    if (status == CPL_ERROR_NONE && fprintf(paf, "\n") != 1)
        status = CPL_ERROR_FILE_IO;

    if (status == CPL_ERROR_NONE) {
        cpl_ensure_code(fclose(paf) == 0, CPL_ERROR_FILE_IO);
    } else {
        (void)fclose(paf);
    }

    return status;

}
