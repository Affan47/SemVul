gl_cairo_markup_margin_rect_path (cairo_t                 *cr,
                                  const lglTemplateMarkup *markup,
                                  glLabel                 *label)
{
        const lglTemplate      *template;
        const lglTemplateFrame *frame;
        gdouble                 w, h, r, m;

        gl_debug (DEBUG_PATH, "START");

        template = gl_label_get_template (label);
        frame = (lglTemplateFrame *)template->frames->data;

        m = markup->margin.size;

        lgl_template_frame_get_size (frame, &w, &h);
	w = w - 2*m;
	h = h - 2*m;
        r = MAX (frame->rect.r - m, 0.0);

        if ( r == 0.0 )
        {
                cairo_rectangle (cr, m, m, w, h);
        }
        else
        {
                cairo_new_path (cr);
                cairo_arc_negative (cr, m+r,   m+r,   r, 3*G_PI/2, G_PI);
                cairo_arc_negative (cr, m+r,   m+h-r, r, G_PI,     G_PI/2);
                cairo_arc_negative (cr, m+w-r, m+h-r, r, G_PI/2,   0.);
                cairo_arc_negative (cr, m+w-r, m+r,   r, 2*G_PI,   3*G_PI/2);
                cairo_close_path (cr);
        }

        gl_debug (DEBUG_PATH, "END");
}
