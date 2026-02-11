gtk_scroll_frame_set_arg (GtkObject *object, GtkArg *arg, guint arg_id)
{
	GtkScrollFrame *sf;
	ScrollFramePrivate *priv;

	sf = GTK_SCROLL_FRAME (object);
	priv = sf->priv;

	switch (arg_id) {
	case ARG_HADJUSTMENT:
		gtk_scroll_frame_set_hadjustment (sf, GTK_VALUE_POINTER (*arg));
		break;

	case ARG_VADJUSTMENT:
		gtk_scroll_frame_set_vadjustment (sf, GTK_VALUE_POINTER (*arg));
		break;

	case ARG_HSCROLLBAR_POLICY:
		gtk_scroll_frame_set_policy (sf, GTK_VALUE_ENUM (*arg), priv->vsb_policy);
		break;

	case ARG_VSCROLLBAR_POLICY:
		gtk_scroll_frame_set_policy (sf, priv->hsb_policy, GTK_VALUE_ENUM (*arg));
		break;

	case ARG_FRAME_PLACEMENT:
		gtk_scroll_frame_set_placement (sf, GTK_VALUE_ENUM (*arg));
		break;

	case ARG_SHADOW_TYPE:
		gtk_scroll_frame_set_shadow_type (sf, GTK_VALUE_ENUM (*arg));
		break;

	case ARG_SCROLLBAR_SPACING:
		gtk_scroll_frame_set_scrollbar_spacing (sf, GTK_VALUE_UINT (*arg));
		break;

	default:
		break;
	}
}
