get_profile_var(krb5_context context, int id, const char *varname, char ***out)
{
    krb5_error_code ret;
    const char *path[4];

    *out = NULL;
    path[0] = KRB5_CONF_PLUGINS;
    path[1] = interface_names[id];
    path[2] = varname;
    path[3] = NULL;
    ret = profile_get_values(context->profile, path, out);
    return (ret == PROF_NO_RELATION) ? 0 : ret;
}
