goc_image_get_property (GObject *gobject, guint param_id,
				    GValue *value, GParamSpec *pspec)
{
	GocImage *image = GOC_IMAGE (gobject);

	switch (param_id) {
	case IMAGE_PROP_X:
		g_value_set_double (value, image->x);
		break;

	case IMAGE_PROP_Y:
		g_value_set_double (value, image->y);
		break;

	case IMAGE_PROP_W:
		g_value_set_double (value, image->width);
		break;

	case IMAGE_PROP_H:
		g_value_set_double (value, image->height);
		break;

	case IMAGE_PROP_ROTATION:
		g_value_set_double (value, image->rotation);
		break;

	case IMAGE_PROP_IMAGE:
		if (image->image)
			g_value_set_object (value, G_OBJECT (image->image));
		break;

	case IMAGE_PROP_CROP_BOTTOM:
		g_value_set_double (value, image->crop_bottom);
		break;

	case IMAGE_PROP_CROP_LEFT:
		g_value_set_double (value, image->crop_left);
		break;

	case IMAGE_PROP_CROP_RIGHT:
		g_value_set_double (value, image->crop_right);
		break;

	case IMAGE_PROP_CROP_TOP:
		g_value_set_double (value, image->crop_top);
		break;

	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, param_id, pspec);
		return;
	}
}
