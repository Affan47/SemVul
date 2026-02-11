ganv_box_set_property(GObject*      object,
                      guint         prop_id,
                      const GValue* value,
                      GParamSpec*   pspec)
{
	g_return_if_fail(object != NULL);
	g_return_if_fail(GANV_IS_BOX(object));

	GanvBox*       box    = GANV_BOX(object);
	GanvBoxImpl*   impl   = box->impl;
	GanvBoxCoords* coords = &impl->coords;

	switch (prop_id) {
		SET_CASE(X1, double, coords->x1);
		SET_CASE(Y1, double, coords->y1);
		SET_CASE(X2, double, coords->x2);
		SET_CASE(Y2, double, coords->y2);
		SET_CASE(RADIUS_TL, double, impl->radius_tl);
		SET_CASE(RADIUS_TR, double, impl->radius_tr);
		SET_CASE(RADIUS_BR, double, impl->radius_br);
		SET_CASE(RADIUS_BL, double, impl->radius_bl);
		SET_CASE(STACKED, boolean, coords->stacked);
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}
