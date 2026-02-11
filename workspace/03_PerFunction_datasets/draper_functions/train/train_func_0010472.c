path_get_config(wcstring &path)
{
    static const wcstring result = path_create_config();
    path = result;
    return ! result.empty();
}
