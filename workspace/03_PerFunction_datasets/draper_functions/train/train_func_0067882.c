set_double (const char * section, const char * name, double value)
{
    char * string = double_to_string (value);
    g_return_if_fail (string);
    set_string (section, name, string);
    g_free (string);
}
