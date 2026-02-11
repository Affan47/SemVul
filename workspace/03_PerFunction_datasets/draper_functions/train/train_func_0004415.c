image_view_clear( ImageView* iv )
{
    if( iv->idle_handler )
    {
        g_source_remove( iv->idle_handler );
        iv->idle_handler = 0;
    }

    if( iv->pix )
    {
        g_object_unref( iv->pix );
        iv->pix = NULL;
        calc_image_area( iv );
    }


}
