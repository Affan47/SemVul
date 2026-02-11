gtkb_theme_get_coord_at_x(gint x) {
        if(gtkbTheme) {
  		return (x - 1) / gtkbTheme->emptycell.xsize;
        }
        return -1;
}
