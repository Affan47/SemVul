indirect_client_create (GdmXdmcpDisplayFactory *factory,
                        GdmAddress             *dsp_address)
{
        IndirectClient *ic;

        ic = g_new0 (IndirectClient, 1);
        ic->dsp_address = gdm_address_copy (dsp_address);

        factory->priv->indirect_clients = g_slist_prepend (factory->priv->indirect_clients, ic);

        return ic;
}
