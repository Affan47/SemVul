parse_file(char *filename)
{
    int val;
    int ret = OMPI_SUCCESS;
    bool first_section = true, first_coll = true;
    coll_config_t coll_config;

    memset (&coll_config, 0, sizeof (coll_config));
    reset_collective(&coll_config);


    coll_ml_config_yyin = fopen(filename, "r");
    if (NULL == coll_ml_config_yyin) {
        ML_ERROR(("Failed to open config file %s", filename));
        ret = OMPI_ERR_NOT_FOUND;
        goto cleanup;
    }


    coll_ml_config_parse_done = false;
    coll_ml_config_yynewlines = 1;
    coll_ml_config_init_buffer(coll_ml_config_yyin);
    while (!coll_ml_config_parse_done) {
        val = coll_ml_config_yylex();
        switch (val) {
        case COLL_ML_CONFIG_PARSE_DONE:
        case COLL_ML_CONFIG_PARSE_NEWLINE:
            break;
        case COLL_ML_CONFIG_PARSE_COLLECTIVE:

            if (!first_coll) {
                ret = save_settings(&coll_config);

                if (OMPI_SUCCESS != ret) {
                    ML_ERROR(("Error in syntax for collective %s", coll_config.coll_name));
                    goto cleanup;
                }
            }


            reset_collective(&coll_config);

            first_coll    = false;
            first_section = true;

            ret = set_collective_name(&coll_config);
            if (OMPI_SUCCESS != ret) {
                goto cleanup;
            }
            break;
        case COLL_ML_CONFIG_PARSE_SECTION:
            if (ML_UNDEFINED == coll_config.coll_id) {
                ML_ERROR(("Collective section wasn't defined !"));
                ret = OMPI_ERROR;
                goto cleanup;
            }

            if (!first_section) {

                ret = save_settings(&coll_config);
                if (OMPI_SUCCESS != ret) {
                    ML_ERROR(("Error in syntax for collective %s section %s", coll_config.coll_name,
                              coll_config.section.section_name));
                    goto cleanup;
                }
            }

            first_section = false;


            reset_section(&coll_config.section);


            ret = set_section_name(&coll_config.section);
            if (OMPI_SUCCESS != ret) {
                goto cleanup;
            }
            break;
        case COLL_ML_CONFIG_PARSE_SINGLE_WORD:
            if (ML_UNDEFINED == coll_config.coll_id ||
                ML_UNDEFINED == coll_config.section.section_id) {
                ML_ERROR(("Collective section or sub-section was not defined !"));
                ret = OMPI_ERROR;
                goto cleanup;
            } else {
                parse_line(&coll_config.section);
            }
            break;

        default:

            ML_ERROR(("Unexpected token!"));
            ret = OMPI_ERROR;
            goto cleanup;
            break;
        }
    }

    save_settings(&coll_config);
    fclose(coll_ml_config_yyin);
    coll_ml_config_yylex_destroy ();
    ret = OMPI_SUCCESS;

cleanup:
    reset_collective(&coll_config);
    if (NULL != key_buffer) {
        free(key_buffer);
        key_buffer = NULL;
        key_buffer_len = 0;
    }
    return ret;
}
