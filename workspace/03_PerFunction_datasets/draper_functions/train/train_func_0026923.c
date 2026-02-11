tgdb_types_delete_item(void *command)
{
    struct tgdb_response *com = (struct tgdb_response *) command;

    if (!com)
        return -1;

    switch (com->header) {
        case TGDB_UPDATE_BREAKPOINTS:
        {
            struct tgdb_list *list =
                    com->choice.update_breakpoints.breakpoint_list;

            tgdb_list_free(list, tgdb_types_breakpoint_free);
            break;
        }
        case TGDB_UPDATE_FILE_POSITION:
        {
            struct tgdb_file_position *tfp =
                    com->choice.update_file_position.file_position;

            free(tfp->absolute_path), tfp->absolute_path = NULL;
            free(tfp->relative_path), tfp->relative_path = NULL;

            free(tfp);
            tfp = NULL;
            break;
        }
        case TGDB_UPDATE_SOURCE_FILES:
        {
            struct tgdb_list *list =
                    com->choice.update_source_files.source_files;
            tgdb_list_free(list, tgdb_types_source_files_free);
            break;
        }
        case TGDB_SOURCES_DENIED:

            break;
        case TGDB_FILENAME_PAIR:
        {
            free((char *) com->choice.filename_pair.absolute_path);
            com->choice.filename_pair.absolute_path = NULL;
            free((char *) com->choice.filename_pair.relative_path);
            com->choice.filename_pair.relative_path = NULL;
            break;
        }
        case TGDB_ABSOLUTE_SOURCE_DENIED:
        {
            struct tgdb_source_file *file =
                    com->choice.absolute_source_denied.source_file;
            free(file->absolute_path);
            file->absolute_path = NULL;
            free(file);
            file = NULL;
            break;
        }
        case TGDB_INFERIOR_EXITED:
        {
            int *status = com->choice.inferior_exited.exit_status;

            free(status);
            status = NULL;
        }
            break;
        case TGDB_UPDATE_COMPLETIONS:
        {
            struct tgdb_list *list =
                    com->choice.update_completions.completion_list;
            tgdb_list_free(list, tgdb_types_source_files_free);
            break;
        }
        case TGDB_UPDATE_CONSOLE_PROMPT_VALUE:
        {
            const char *value =
                    com->choice.update_console_prompt_value.prompt_value;
            free((char *) value);
            value = NULL;
            break;
        }
        case TGDB_QUIT:
        {
            struct tgdb_debugger_exit_status *status =
                    com->choice.quit.exit_status;
            free(status);
            status = NULL;
            break;
        }
    }

    free(com);
    com = NULL;
    return 0;
}
