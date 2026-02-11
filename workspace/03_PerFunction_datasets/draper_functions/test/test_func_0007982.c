gl_merge_text_set_property (GObject      *object,
			    guint         param_id,
			    const GValue *value,
			    GParamSpec   *pspec)
{
	glMergeText *merge_text;

	merge_text = GL_MERGE_TEXT (object);

	switch (param_id) {

	case ARG_DELIM:
		merge_text->priv->delim = g_value_get_char (value);
		gl_debug (DEBUG_MERGE, "ARG \"delim\" = \"%c\"",
			  merge_text->priv->delim);
		break;

        case ARG_LINE1_HAS_KEYS:
                merge_text->priv->line1_has_keys = g_value_get_boolean (value);
		gl_debug (DEBUG_MERGE, "ARG \"line1_has_keys\" = \"%d\"",
			  merge_text->priv->line1_has_keys);
		break;

        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
                break;

        }

}
