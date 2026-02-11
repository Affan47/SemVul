get_string()
{
    switch (arglex_token)
    {
    case arglex_token_number:
    case arglex_token_string:
        {
            nstring result = arglex_value.alv_string;
            arglex();
            return result;
        }

    default:
        usage();
    }
    return "";
}
