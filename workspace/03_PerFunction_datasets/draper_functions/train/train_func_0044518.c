histogram_imager_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
    HistogramImager *self = HISTOGRAM_IMAGER (object);

    switch (prop_id) {

    case PROP_WIDTH:
	g_value_set_uint (value, self->width);
	break;

    case PROP_HEIGHT:
	g_value_set_uint (value, self->height);
	break;

    case PROP_OVERSAMPLE:
	g_value_set_uint (value, self->oversample);
	break;

    case PROP_OVERSAMPLE_ENABLED:
	g_value_set_boolean (value, self->oversample > 1);
	break;

    case PROP_CLAMPED:
	g_value_set_boolean (value, self->clamped);
	break;

    case PROP_EXPOSURE:
	g_value_set_double (value, self->exposure);
	break;

    case PROP_GAMMA:
	g_value_set_double (value, self->gamma);
	break;

    case PROP_OVERSAMPLE_GAMMA:
	g_value_set_double (value, self->oversample_gamma);
	break;

    case PROP_FGALPHA:
	g_value_set_uint (value, self->fgalpha);
	break;

    case PROP_BGALPHA:
	g_value_set_uint (value, self->bgalpha);
	break;

    case PROP_SIZE:
	g_value_set_string_take_ownership (value, g_strdup_printf ("%dx%d", self->width, self->height));
	break;

    case PROP_FGCOLOR:
	g_value_set_string_take_ownership (value, describe_color (&self->fgcolor));
	break;

    case PROP_BGCOLOR:
	g_value_set_string_take_ownership (value, describe_color (&self->bgcolor));
	break;

    case PROP_FGCOLOR_GDK:
	g_value_set_boxed (value, &self->fgcolor);
	break;

    case PROP_BGCOLOR_GDK:
	g_value_set_boxed (value, &self->bgcolor);
	break;

    default:
	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	break;
    }
}
