gda_models_provider_get_server_version (GdaServerProvider *provider, GdaConnection *cnc)
{
	ModelsConnectionData *cdata;

        g_return_val_if_fail (GDA_IS_CONNECTION (cnc), NULL);
        g_return_val_if_fail (gda_connection_get_provider (cnc) == provider, NULL);

        cdata = (ModelsConnectionData*) gda_virtual_connection_internal_get_provider_data (GDA_VIRTUAL_CONNECTION (cnc));
        if (!cdata)
                return FALSE;
        TO_IMPLEMENT;
        return NULL;
}
