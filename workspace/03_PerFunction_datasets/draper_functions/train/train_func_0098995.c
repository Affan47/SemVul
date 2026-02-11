ganv_module_point(GanvItem* item,
                  double x, double y,
                  int cx, int cy,
                  GanvItem** actual_item)
{
	GanvModule* module = GANV_MODULE(item);

	double d = GANV_ITEM_CLASS(parent_class)->point(
		item, x, y, cx, cy, actual_item);

	if (!*actual_item) {

		return d;
	}

	FOREACH_PORT(module->impl->ports, p) {
		GanvItem* const port = GANV_ITEM(*p);

		*actual_item = NULL;
		d = GANV_ITEM_GET_CLASS(port)->point(
			port,
			x - port->x, y - port->y,
			cx, cy,
			actual_item);

		if (*actual_item) {

			return d;
		}
	}


	*actual_item = item;
	return 0.0;
}
