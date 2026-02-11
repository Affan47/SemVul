auto_shrink_font_size (cairo_t     *cr,
                       gchar       *family,
                       gdouble      size,
                       PangoWeight  weight,
                       PangoStyle   style,
                       gchar       *text,
                       gdouble      width)
{
        PangoLayout          *layout;
        PangoFontDescription *desc;
        gint                  iw, ih;
        gdouble               layout_width;
        gdouble               new_size;

        layout = pango_cairo_create_layout (cr);

        desc = pango_font_description_new ();
        pango_font_description_set_family (desc, family);
        pango_font_description_set_weight (desc, weight);
        pango_font_description_set_style  (desc, style);
        pango_font_description_set_size   (desc, size * PANGO_SCALE);

        pango_layout_set_font_description (layout, desc);
        pango_font_description_free       (desc);

        pango_layout_set_text (layout, text, -1);
        pango_layout_set_width (layout, -1);
        pango_layout_get_size (layout, &iw, &ih);
        layout_width = (gdouble)iw / (gdouble)PANGO_SCALE;

        g_object_unref (layout);

        g_print ("Object w = %g, layout w = %g\n", width, layout_width);

        if ( layout_width > width )
        {

                new_size = size * (width-2*GL_LABEL_TEXT_MARGIN)/layout_width;


                new_size = (int)(new_size*2.0) / 2.0;


                if (new_size < 1.0)
                {
                        new_size = 1.0;
                }
        }
        else
        {
                new_size = size;
        }

        return new_size;
}
