lgl_vendor_free (lglVendor *vendor)
{

        if ( vendor != NULL )
        {
                g_free (vendor->name);
                vendor->name = NULL;

                g_free (vendor->url);
                vendor->url = NULL;

                g_free (vendor);
        }

}
