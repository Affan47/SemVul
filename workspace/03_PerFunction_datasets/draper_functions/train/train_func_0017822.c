de_jong_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec) {
    DeJong *self = DE_JONG(object);

    switch (prop_id) {

    case PROP_A:
	g_value_set_double(value, self->param.a);
	break;

    case PROP_B:
	g_value_set_double(value, self->param.b);
	break;

    case PROP_C:
	g_value_set_double(value, self->param.c);
	break;

    case PROP_D:
	g_value_set_double(value, self->param.d);
	break;

    case PROP_ZOOM:
	g_value_set_double(value, self->zoom);
	break;

    case PROP_ASPECT:
	g_value_set_double(value, self->aspect);
	break;

    case PROP_XOFFSET:
	g_value_set_double(value, self->xoffset);
	break;

    case PROP_YOFFSET:
	g_value_set_double(value, self->yoffset);
	break;

    case PROP_ROTATION:
	g_value_set_double(value, self->rotation);
	break;

    case PROP_BLUR_RADIUS:
	g_value_set_double(value, self->blur_radius);
	break;

    case PROP_BLUR_RATIO:
	g_value_set_double(value, self->blur_ratio);
	break;

    case PROP_TILEABLE:
	g_value_set_boolean(value, self->tileable);
	break;

    case PROP_EMPHASIZE_TRANSIENT:
	g_value_set_boolean(value, self->emphasize_transient);
	break;

    case PROP_TRANSIENT_ITERATIONS:
	g_value_set_uint(value, self->transient_iterations);
	break;

    case PROP_INITIAL_CONDITIONS:
	g_value_set_enum(value, self->initial_conditions);
	break;

    case PROP_INITIAL_XOFFSET:
	g_value_set_double(value, self->initial_xoffset);
	break;

    case PROP_INITIAL_YOFFSET:
	g_value_set_double(value, self->initial_yoffset);
	break;

    case PROP_INITIAL_XSCALE:
	g_value_set_double(value, self->initial_xscale);
	break;

    case PROP_INITIAL_YSCALE:
	g_value_set_double(value, self->initial_yscale);
	break;

    default:
	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	break;
    }
}
