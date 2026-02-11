pixbuf_renderer_get_property(GObject *object, guint prop_id,
					 GValue *value, GParamSpec *pspec)
{
	PixbufRenderer *pr;

	pr = PIXBUF_RENDERER(object);

	switch (prop_id)
		{
		case PROP_ZOOM_MIN:
			g_value_set_double(value, pr->zoom_min);
			break;
		case PROP_ZOOM_MAX:
			g_value_set_double(value, pr->zoom_max);
			break;
		case PROP_ZOOM_QUALITY:
			g_value_set_uint(value, pr->zoom_quality);
			break;
		case PROP_ZOOM_2PASS:
			g_value_set_boolean(value, pr->zoom_2pass);
			break;
		case PROP_ZOOM_EXPAND:
			g_value_set_boolean(value, pr->zoom_expand);
			break;
		case PROP_DITHER_QUALITY:
			g_value_set_uint(value, pr->dither_quality);
			break;
		case PROP_SCROLL_RESET:
			g_value_set_uint(value, pr->scroll_reset);
			break;
		case PROP_DELAY_FLIP:
			g_value_set_boolean(value, pr->delay_flip);
			break;
		case PROP_LOADING:
			g_value_set_boolean(value, pr->loading);
			break;
		case PROP_COMPLETE:
			g_value_set_boolean(value, pr->complete);
			break;
		case PROP_CACHE_SIZE_DISPLAY:

			break;
		case PROP_CACHE_SIZE_TILES:
			g_value_set_uint(value, pr->source_tiles_cache_size);
			break;
		case PROP_WINDOW_FIT:
			g_value_set_boolean(value, pr->window_fit);
			break;
		case PROP_WINDOW_LIMIT:
			g_value_set_boolean(value, pr->window_limit);
			break;
		case PROP_WINDOW_LIMIT_VALUE:
			g_value_set_uint(value, pr->window_limit_size);
			break;
		case PROP_AUTOFIT_LIMIT:
			g_value_set_boolean(value, pr->autofit_limit);
			break;
		case PROP_AUTOFIT_LIMIT_VALUE:
			g_value_set_uint(value, pr->autofit_limit_size);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
			break;
		}
}
