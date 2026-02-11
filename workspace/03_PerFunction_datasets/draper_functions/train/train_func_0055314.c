rgba2gdk (guint rgba, GdkColor *color, guint16 *alpha)
{
     guint16 r,g,b;
     guint tmp;


     if (color == NULL) {
          sat_log_log (SAT_LOG_LEVEL_BUG,
                          _("%s:%s: %s called with color = NULL"),
                          __FILE__, __LINE__, __FUNCTION__);
          return;
     }
     if (alpha == NULL) {
          sat_log_log (SAT_LOG_LEVEL_BUG,
                          _("%s:%s: %s called with alpha = NULL"),
                          __FILE__, __LINE__, __FUNCTION__);
          return;
     }


     tmp = rgba & 0xFF000000;
     r = (guint16) (tmp >> 24);


     tmp = rgba & 0x00FF0000;
     g = (guint16) (tmp >> 16);


     tmp = rgba & 0x0000FF00;
     b = (guint16) (tmp >> 8);


     *alpha = (guint16) (257 * (rgba & 0x000000FF));


     color->red   = 257 * r;
     color->green = 257 * g;
     color->blue  = 257 * b;
}
