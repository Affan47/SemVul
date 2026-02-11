draw_label_outlines (cairo_t           *cr,
		     lglTemplate       *template,
		     gdouble            scale)
{
	const lglTemplateFrame *frame;
	gint                    i, n_labels;
	lglTemplateOrigin      *origins;

	gl_debug (DEBUG_MINI_PREVIEW, "START");

	cairo_save (cr);

	cairo_set_line_width (cr, LABEL_OUTLINE_WIDTH_PIXELS/scale);

        frame = (lglTemplateFrame *)template->frames->data;

	n_labels = lgl_template_frame_get_n_labels (frame);
	origins  = lgl_template_frame_get_origins (frame);

	for ( i=0; i < n_labels; i++ ) {

		draw_label_outline(cr, template, origins[i].x, origins[i].y);

	}

	g_free (origins);

	cairo_restore (cr);

	gl_debug (DEBUG_MINI_PREVIEW, "END");
}
