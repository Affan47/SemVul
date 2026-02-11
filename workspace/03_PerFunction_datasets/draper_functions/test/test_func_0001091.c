parser_save_section(struct parser_obj *po)
{
    int error = EOK;
    uint32_t mergemode;
    int merge = 0;

    TRACE_FLOW_ENTRY();

    if (po->sec) {

        TRACE_INFO_STRING("Section exists.", "");


        error = check_section_collision(po);
        if (error) {
            TRACE_ERROR_NUMBER("Failed to check for collision", error);
            return error;
        }

        if (po->merge_sec) {

            TRACE_INFO_STRING("Merge collision detected", "");

            mergemode = po->collision_flags & INI_MS_MASK;

            switch (mergemode) {
            case INI_MS_ERROR:

                TRACE_INFO_STRING("Reporting error", "duplicate section");
                error = save_error(po->el,
                                   po->seclinenum,
                                   ERR_DUPSECTION,
                                   ERROR_TXT);
                if (error) {
                    TRACE_ERROR_NUMBER("Failed to "
                                       "save error",
                                        error);
                    return error;
                }

                TRACE_FLOW_RETURN(EEXIST);
                return EEXIST;

            case INI_MS_PRESERVE:

                TRACE_INFO_STRING("Preserve mode", "");
                col_destroy_collection_with_cb(
                                        po->sec,
                                        ini_cleanup_cb,
                                        NULL);
                po->sec = NULL;
                break;

            case INI_MS_OVERWRITE:

                TRACE_INFO_STRING("Ovewrite mode", "");
                error = empty_section(po->merge_sec);
                if (error) {
                    TRACE_ERROR_NUMBER("Failed to "
                                       "empty section",
                                        error);
                    return error;
                }
                merge = 1;
                break;

            case INI_MS_DETECT:

                TRACE_INFO_STRING("Detect mode", "");
                po->merge_error = EEXIST;
                error = save_error(po->el,
                                   po->seclinenum,
                                   ERR_DUPSECTION,
                                   ERROR_TXT);
                if (error) {
                    TRACE_ERROR_NUMBER("Failed to "
                                       "save error",
                                        error);
                    return error;
                }
                merge = 1;
                break;

            case INI_MS_MERGE:

            default:
                TRACE_INFO_STRING("Merge mode", "");
                merge = 1;
                break;
            }

            if (merge) {
                error = merge_section(po);
                if (error) {
                    TRACE_ERROR_NUMBER("Failed to merge section", error);
                    return error;
                }
            }

            po->merge_sec = NULL;
        }
        else {

            TRACE_INFO_STRING("Now adding collection", "");
            error = col_add_collection_to_collection(po->top,
                                                     NULL, NULL,
                                                     po->sec,
                                                     COL_ADD_MODE_EMBED);

            if (error) {
                TRACE_ERROR_NUMBER("Failed to embed section", error);
                return error;
            }

            po->sec = NULL;
        }
    }

    TRACE_FLOW_EXIT();
    return EOK;

}
