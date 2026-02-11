try_hostname_fqdn(nstring &result)
{
    result = run_a_command("hostname");
    const char *dot = strchr(result.c_str(), '.');
    if (!dot)
        return false;
    result = nstring(dot + 1);
    return is_a_valid_domain_string(result);
}
