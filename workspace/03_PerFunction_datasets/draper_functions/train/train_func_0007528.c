move_x11(struct display *disp, int logical, int legend, hwloc_topology_t topology)
{
  if (disp->width <= disp->screen_width) {
    disp->x = 0;
  } else {
    if (disp->x < 0)
      disp->x = 0;
    if (disp->x >= disp->width - disp->screen_width)
      disp->x = disp->width - disp->screen_width;
  }

  if (disp->height <= disp->screen_height) {
    disp->y = 0;
  } else {
    if (disp->y < 0)
      disp->y = 0;
    if (disp->y >= disp->height - disp->screen_height)
      disp->y = disp->height - disp->screen_height;
  }

 if (disp->screen_width > disp->width && disp->screen_height > disp->height
   && (disp->screen_width != disp->last_screen_width
   || disp->screen_height != disp->last_screen_height)) {
    disp->last_screen_width = disp->screen_width;
    disp->last_screen_height = disp->screen_height;
    fontsize = disp->orig_fontsize;
    gridsize = disp->orig_gridsize;
    if (disp->screen_width > disp->width) {
      fontsize = disp->orig_fontsize * disp->screen_width / disp->width;
      gridsize = disp->orig_gridsize * disp->screen_width / disp->width;
    }
    if (disp->screen_height > disp->height) {
      unsigned int new_fontsize = disp->orig_fontsize * disp->screen_height / disp->height;
      unsigned int new_gridsize = disp->orig_gridsize * disp->screen_height / disp->height;
      if (new_fontsize < fontsize)
	fontsize = new_fontsize;
      if (new_gridsize < gridsize)
	gridsize = new_gridsize;
    }

    x11_destroy(disp);
    x11_create(disp, disp->screen_width, disp->screen_height);
    topo_cairo_paint(&x11_draw_methods, logical, legend, topology, disp->cs);
  }
}
