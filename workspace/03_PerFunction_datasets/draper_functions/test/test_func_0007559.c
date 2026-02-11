gdm_display_factory_start (GdmDisplayFactory *factory)
{
        gboolean ret;

        g_return_val_if_fail (GDM_IS_DISPLAY_FACTORY (factory), FALSE);

        g_object_ref (factory);
        ret = GDM_DISPLAY_FACTORY_GET_CLASS (factory)->start (factory);
        g_object_unref (factory);

        return ret;
}
