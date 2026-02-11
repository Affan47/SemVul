gdip_metafile_play_setup (GpMetafile *metafile, GpGraphics *graphics, int x, int y, int width, int height)
{
	int i, n;
	MetaObject *obj;
	MetafilePlayContext *context;

	int stride = width * 4;
	int size = height * stride;

	if (!metafile || !graphics)
		return NULL;

	context = GdipAlloc (sizeof (MetafilePlayContext));
	context->metafile = metafile;
	context->graphics = graphics;
	context->use_path = FALSE;
	context->path = NULL;


	GdipGetWorldTransform (graphics, &context->initial);
#ifdef DEBUG_METAFILE
	MetafileHeader *mh = &metafile->metafile_header;
	GpMatrix *m = &context->initial;
	g_warning ("\nMetafileHeader X %d, Y %d, W %d, H %d", mh->X, mh->Y, mh->Width, mh->Height);
	g_warning ("\n\tinitial matrix %g %g %g %g %g %g", m->xx, m->yx, m->xy, m->yy, m->x0, m->y0);
#endif
	context->x = x;
	context->y = y;
	context->width = width;
	context->height = height;

	GdipTranslateWorldTransform (graphics, -metafile->metafile_header.X, -metafile->metafile_header.Y, MatrixOrderPrepend);
	GdipGetWorldTransform (graphics, &context->matrix);


	context->fill_mode = FillModeAlternate;
	context->map_mode = MM_TEXT;
	context->miter_limit = 10.0f;
	context->selected_pen = -1;
	context->selected_brush = -1;
	context->selected_font = -1;
	context->selected_palette = -1;


	context->created.type = METAOBJECT_TYPE_EMPTY;
	context->created.ptr = NULL;


	context->stock_pen_white = NULL;
	context->stock_pen_black = NULL;
	context->stock_pen_null = NULL;
	context->stock_brush_white = NULL;
	context->stock_brush_ltgray = NULL;
	context->stock_brush_gray = NULL;
	context->stock_brush_dkgray = NULL;
	context->stock_brush_black = NULL;
	context->stock_brush_null = NULL;


	switch (context->metafile->metafile_header.Type) {
	case METAFILETYPE_WMFPLACEABLE:
	case METAFILETYPE_WMF:
		context->objects_count = metafile->metafile_header.WmfHeader.mtNoObjects;
		break;
	case METAFILETYPE_EMF:
	case METAFILETYPE_EMFPLUSONLY:
	case METAFILETYPE_EMFPLUSDUAL:
		context->objects_count = metafile->metafile_header.EmfHeader.nHandles + 1;
		break;
	default:
		GdipFree (context);
		return NULL;
	}
	context->objects = (MetaObject*) GdipAlloc (context->objects_count * sizeof (MetaObject));
	if (!context->objects) {
		GdipFree (context);
		return NULL;
	}
	obj = context->objects;
	for (i = 0; i < context->objects_count; i++) {
		obj->type = METAOBJECT_TYPE_EMPTY;
		obj->ptr = NULL;
		obj++;
	}

	return context;
}
