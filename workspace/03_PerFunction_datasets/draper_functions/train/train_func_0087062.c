config_with_metadata(const char *application,
                                FILE *config_file,
                                const char *config_source,
                                struct collection_item **ini_config,
                                int error_level,
                                struct collection_item **error_list,
                                uint32_t metaflags,
                                struct collection_item **metadata)
{
    int error;
    int created = 0;
    struct collection_item *lines = NULL;

#ifdef HAVE_VALIDATION
    int created_lines = 0;
#endif

    TRACE_FLOW_STRING("config_from_file", "Entry");


    if (*ini_config == NULL) {
        error = col_create_collection(ini_config,
                                      application,
                                      COL_CLASS_INI_CONFIG);
        if (error != EOK) {
            TRACE_ERROR_NUMBER("Failed to create collection", error);
            return error;
        }
        created = 1;
    }

    else if (((col_is_of_class(*ini_config, COL_CLASS_INI_CONFIG))== 0) &&
             ((col_is_of_class(*ini_config, COL_CLASS_INI_META))== 0)) {
        TRACE_ERROR_NUMBER("Wrong collection type", EINVAL);
        return EINVAL;
    }

#ifdef HAVE_VALIDATION

    error = col_create_collection(lines,
                                    application,
                                    COL_CLASS_INI_LINES);
    if (error != EOK) {
        TRACE_ERROR_NUMBER("Failed to create collection", error);
        if (created) {
            col_destroy_collection(*ini_config);
            *ini_config = NULL;
        }
        return error;
    }
    created_lines = 1;
#else

    lines = NULL;
#endif


    error = ini_to_collection(config_file, config_source,
                              *ini_config, error_level,
                              error_list, lines);

    if (error && created) {
        col_destroy_collection(*ini_config);
        *ini_config = NULL;
    }


    TRACE_FLOW_NUMBER("config_from_file. Returns", error);
    return error;
}
