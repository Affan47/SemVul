indent_multiple_files(void)
{
    exit_values_ty exit_status = total_success;

    int i;


    for (i = 0; input_files; i++, input_files--)
    {
        exit_values_ty status;
        struct stat file_stats;

        in_name = in_file_names[i];
        out_name = in_file_names[i];
        current_input = read_file(in_file_names[i], &file_stats);

        open_output(out_name, "r+");

        make_backup(current_input, &file_stats);


        reopen_output_trunc(out_name);

        reset_parser();
        status = indent (current_input);

        if (status > exit_status)
        {
            exit_status = status;
        }

        if (settings.preserve_mtime)
        {
            close_output(&file_stats, out_name);
        }
        else
        {
            close_output(NULL, out_name);
        }
    }

    return exit_status;
}
