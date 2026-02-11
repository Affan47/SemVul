set_tristate_from_env (TriState * result, tchar const * envvar_name)
{
    tstring envvar_value;
    bool exists = internal::get_env_var (envvar_value, envvar_name);
    bool value = false;
    if (exists && internal::parse_bool (value, envvar_value) && value)
        *result = TriTrue;
    else
        *result = TriFalse;
}
