handle_redraw( FL_IMAGE  * im,
               FL_WINDOW   win )
{
    if ( im->double_buffer && im->pixmap )
    {
        im->win = im->pixmap;
        im->display_markers( im );
        im->display_text( im );
        im->win = win;
        flimage_swapbuffer( im );
    }
    else
    {
        im->win = win;
        displayXImage( im );
        im->display_markers( im );
        im->display_text( im );
    }
}
