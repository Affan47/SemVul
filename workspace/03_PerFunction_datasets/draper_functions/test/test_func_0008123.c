border_get_border_background(
	pixmap_background_type *bg, common_decorations_type *cd,
	rectangle *part_g, rectangle *relative_g, int *free_bg_pixmap, Window w)
{
	*free_bg_pixmap = False;

	if (cd->texture_pixmap)
	{
		bg->flags.use_pixmap = 1;
		bg->pixmap.p = cd->texture_pixmap;
		bg->pixmap.g.width = cd->texture_pixmap_width;
		bg->pixmap.g.height = cd->texture_pixmap_height;
		bg->pixmap.shape = None;
		bg->pixmap.alpha = None;
		bg->pixmap.depth = Pdepth;
		bg->pixmap.flags.is_tiled = 1;
		bg->pixmap.flags.is_stretched = 0;
		bg->pixmap.fra.mask = 0;
	}
	else if (cd->bg_border_cs >= 0 &&
		 !CSET_IS_TRANSPARENT_PR(cd->bg_border_cs))
	{
		colorset_t *cs_t = &Colorset[cd->bg_border_cs];
		XGCValues xgcv;

		if (CSET_IS_TRANSPARENT_ROOT(cd->bg_border_cs))
		{
			bg->pixmap.p = CreateBackgroundPixmap(
				dpy, w, part_g->width, part_g->height, cs_t,
				Pdepth, Scr.BordersGC, False);
		}
		else
		{

			if (cd->dynamic_cd.frame_pixmap == None)
			{
				border_get_frame_pixmap(cd, relative_g);
			}
			bg->pixmap.p = XCreatePixmap(
				dpy, cd->dynamic_cd.frame_pixmap, part_g->width,
				part_g->height, Pdepth);
			xgcv.fill_style = FillTiled;
			xgcv.tile = cd->dynamic_cd.frame_pixmap;
			xgcv.ts_x_origin = - relative_g->x;
			xgcv.ts_y_origin = - relative_g->y;
			XChangeGC(
				dpy, Scr.BordersGC, GCTile | GCTileStipXOrigin |
				GCTileStipYOrigin | GCFillStyle, &xgcv);
			XFillRectangle(
				dpy, bg->pixmap.p, Scr.BordersGC, 0, 0,
				part_g->width, part_g->height);
			xgcv.fill_style = FillSolid;
			XChangeGC(dpy, Scr.BordersGC, GCFillStyle, &xgcv);
		}
		bg->pixmap.g.width = part_g->width;
		bg->pixmap.g.height = part_g->height;
		bg->flags.use_pixmap = 1;
		bg->pixmap.shape = None;
		bg->pixmap.alpha = None;
		bg->pixmap.depth = Pdepth;
		bg->pixmap.flags.is_tiled = 1;
		bg->pixmap.flags.is_stretched = 0;
		bg->pixmap.fra.mask = 0;
		*free_bg_pixmap = True;
	}
	else
	{
		bg->flags.use_pixmap = 0;
		bg->pixel = cd->attributes.background_pixel;
	}

	return;
}
