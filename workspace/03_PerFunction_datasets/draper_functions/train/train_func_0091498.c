gog_view_get_tip_at_point (GogView *view, double x, double y)
{
	GogViewClass *klass = GOG_VIEW_GET_CLASS (view);
	return (klass->get_tip_at_point != NULL)? (klass->get_tip_at_point) (view, x, y): NULL;
}
