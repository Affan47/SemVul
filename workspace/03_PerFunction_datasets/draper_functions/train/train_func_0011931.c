read_svg_data(void)
{
   cairo_surface_t *surface;
   cairo_t *cr;

   shm_alloc(width * height * (sizeof(DATA32)));
   if (!shm_addr) return 0;

   memset(shm_addr, 0, width * height * sizeof (DATA32));
   surface = cairo_image_surface_create_for_data((unsigned char *)shm_addr, CAIRO_FORMAT_ARGB32,
                                                 width, height, width * sizeof(DATA32));;
   if (!surface) return 0;

   cr = cairo_create(surface);
   if (!cr) return 0;

   cairo_scale(cr, (double) width / dim.em, (double) height / dim.ex);
   rsvg_handle_render_cairo(rsvg, cr);
   cairo_surface_destroy(surface);
   cairo_destroy(cr);

   return 1;
}
