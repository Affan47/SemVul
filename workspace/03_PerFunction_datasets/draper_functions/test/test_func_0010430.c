s4u2proxy_set_attribute(krb5_context kcontext,
                        krb5_authdata_context context,
                        void *plugin_context,
                        void *request_context,
                        krb5_boolean complete,
                        const krb5_data *attribute,
                        const krb5_data *value)
{

    if (!data_eq(*attribute, s4u2proxy_transited_services_attr))
        return ENOENT;

    return EPERM;
}
