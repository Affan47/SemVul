handle_token_nparen(
    BOOLEAN        * force_nl,
    exit_values_ty * file_exit_value,
    BOOLEAN        * last_else,
    BOOLEAN        * pbreak_line)
{
    parser_state_tos->in_stmt = false;
    if (*token == 'e')
    {
        if (e_code != s_code && (!settings.cuddle_else || e_code[-1] != '}'))
        {
            if (settings.verbose)
            {
                WARNING (_("Line broken"), 0, 0);
            }

            dump_line (true, &paren_target, pbreak_line);
            parser_state_tos->want_blank = false;
        }


        *force_nl = true;

        *last_else = 1;

        if (parse (elselit) != total_success)
        {
            *file_exit_value = indent_error;
        }
    }
    else
    {
        if (e_code != s_code)
        {


            if (settings.verbose)
            {
                WARNING (_("Line broken"), 0, 0);
            }

            dump_line (true, &paren_target, pbreak_line);
            parser_state_tos->want_blank = false;
        }

        *force_nl = true;

        *last_else = 0;

        if (parse (dolit) != total_success)
        {
            *file_exit_value = indent_error;
        }
    }
}
