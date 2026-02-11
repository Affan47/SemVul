render()
{
    if (!_cairo_offscreen)  return;


    cairo_set_source_surface(_cairo_handle,
    	cairo_get_target(_cairo_offscreen), 0, 0);
    cairo_paint(_cairo_handle);
}
