cairogen_begin_page(GVJ_t * job)
{
    cairo_t *cr = (cairo_t *) job->context;
    cairo_surface_t *surface;
    cairo_status_t status;

    if (cr == NULL) {
        switch (job->render.id) {
        case FORMAT_PS:
#ifdef CAIRO_HAS_PS_SURFACE
	    surface = cairo_ps_surface_create_for_stream (writer,
			job, job->width, job->height);
#endif
	    break;
        case FORMAT_PDF:
#ifdef CAIRO_HAS_PDF_SURFACE
	    surface = cairo_pdf_surface_create_for_stream (writer,
			job, job->width, job->height);
#endif
	    break;
        case FORMAT_SVG:
#ifdef CAIRO_HAS_SVG_SURFACE
	    surface = cairo_svg_surface_create_for_stream (writer,
			job, job->width, job->height);
#endif
	    break;
        case FORMAT_CAIRO:
        case FORMAT_PNG:
        default:
	    if (job->width >= CAIRO_XMAX || job->height >= CAIRO_YMAX) {
		double scale = MIN((double)CAIRO_XMAX / job->width,
			(double)CAIRO_YMAX / job->height);
		job->width *= scale;
		job->height *= scale;
		job->scale.x *= scale;
		job->scale.y *= scale;
                fprintf(stderr,
                        "%s: graph is too large for cairo-renderer bitmaps. Scaling by %g to fit\n",
                        job->common->cmdname, scale);
	    }
	    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
			job->width, job->height);
            if (job->common->verbose)
                fprintf(stderr,
                        "%s: allocating a %dK cairo image surface (%d x %d pixels)\n",
                        job->common->cmdname,
			ROUND(job->width * job->height * 4 / 1024.),
			job->width, job->height);
	    break;
        }
	status = cairo_surface_status(surface);
        if (status != CAIRO_STATUS_SUCCESS)  {
		fprintf(stderr, "%s: failure to create cairo surface: %s\n",
			job->common->cmdname,
			cairo_status_to_string(status));
		cairo_surface_destroy (surface);
		return;
	}
        cr = cairo_create(surface);
        cairo_surface_destroy (surface);
        job->context = (void *) cr;
    }

    cairo_scale(cr, job->scale.x, job->scale.y);
    cairo_rotate(cr, -job->rotation * M_PI / 180.);
    cairo_translate(cr, job->translation.x, -job->translation.y);

    cairo_rectangle(cr, job->clip.LL.x, - job->clip.LL.y,
	    job->clip.UR.x - job->clip.LL.x, - (job->clip.UR.y - job->clip.LL.y));
    cairo_clip(cr);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
}
